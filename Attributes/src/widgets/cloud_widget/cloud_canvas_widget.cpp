/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWheelEvent>

#include "attributes/widgets/cloud_widget.hpp"

namespace attr
{

// helper

QPointF qgraphicsitem_relative_coordinates(QGraphicsItem *item, QGraphicsView *view)
{
  QPointF position = 0.5f * (item->boundingRect().topLeft() +
                             item->boundingRect().bottomRight());
  QPointF scene_pos = item->mapToScene(position);
  QPoint  viewport_pos = view->mapFromScene(scene_pos);
  QPointF view_pos = view->viewport()->mapToParent(viewport_pos);

  return view_pos;
}

// class

CloudCanvasWidget::CloudCanvasWidget(CloudAttribute *p_attr, QWidget *parent)
    : QGraphicsView(parent), p_attr(p_attr)
{
  int width = DEFAULT_CANVAS_WIDTH;

  this->setFixedSize(QSize(width + 2, width + 2));
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // setup scene
  this->setScene(new QGraphicsScene(parent));
  this->scene()->setSceneRect(0, 0, width, width);

  // background
  this->scene()->addRect(QRectF(0.f, 0.f, this->width(), this->height()),
                         QPen(Qt::black),
                         QBrush(Qt::black));

  this->scene()->addRect(
      QRectF(margin, margin, this->width() - 2 * margin, this->height() - 2 * margin),
      QPen(Qt::white, Qt::DotLine),
      QBrush(Qt::black));

  // update scene based on the input attribute
  this->update_scene();
  this->update_point_colors();
}

void CloudCanvasWidget::add_point(QPointF event_pos, float point_value)
{
  QPoint  pos = event_pos.toPoint() - QPoint(this->radius / 2, this->radius / 2);
  QPointF new_point = this->mapFromGlobal(pos);

  QGraphicsEllipseItem *ellipse_item = this->scene()->addEllipse(
      QRectF(new_point.x(), new_point.y(), radius, radius),
      QPen(Qt::white),
      QBrush(Qt::black));

  // use `id_point_data` data storage to keep track of the value
  // assign to the point
  ellipse_item->setData(this->id_point_data, point_value);
  ellipse_item->setFlag(QGraphicsItem::ItemIsMovable);

  this->update_attribute_from_widget();
  this->update_point_colors();
}

void CloudCanvasWidget::clear()
{
  this->clear_scene();
  this->update_attribute_from_widget();
}

void CloudCanvasWidget::clear_scene()
{
  // only remove the ellipse objects
  QList<QGraphicsItem *> all_items = this->scene()->items();

  for (QGraphicsItem *item : all_items)
  {
    QGraphicsItem *ellipse_item = dynamic_cast<QGraphicsEllipseItem *>(item);
    if (ellipse_item && ellipse_item->type() == QGraphicsEllipseItem::Type)
    {
      this->scene()->removeItem(item);
      delete item;
    }
  }
}

void CloudCanvasWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  QGraphicsView::mouseDoubleClickEvent(event);
  this->add_point(QPointF(event->globalPosition()));
  this->update_attribute_from_widget();
}

void CloudCanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
  QGraphicsView::mouseMoveEvent(event);

  if (this->moving_point && event->buttons() & Qt::LeftButton)
  {
    int x = std::clamp(event->pos().x(),
                       (int)(this->scene()->sceneRect().left() + margin),
                       (int)(this->scene()->sceneRect().right() - margin));
    int y = std::clamp(event->pos().y(),
                       (int)(this->scene()->sceneRect().top() + margin),
                       (int)(this->scene()->sceneRect().bottom() - margin));

    QPointF new_pos = this->mapToScene(QPoint(x, y)) + this->offset;

    this->moving_point->setPos(new_pos);
  }
}

void CloudCanvasWidget::mousePressEvent(QMouseEvent *event)
{
  QGraphicsView::mousePressEvent(event);

  if (event->button() == Qt::LeftButton)
  {
    QPointF        scene_pos = mapToScene(event->pos());
    QGraphicsItem *item = this->scene()->itemAt(scene_pos, QTransform());

    if (item && item->type() == QGraphicsEllipseItem::Type)
    {
      this->moving_point = dynamic_cast<QGraphicsEllipseItem *>(item);
      {
        this->offset = this->moving_point->pos() - scene_pos;
        this->moving_point->setPen(QPen(Qt::white, 3));
        return;
      }
    }
  }

  if (event->button() == Qt::RightButton)
  {
    QPointF        scene_pos = mapToScene(event->pos());
    QGraphicsItem *item = this->scene()->itemAt(scene_pos, QTransform());

    if (item && item->type() == QGraphicsEllipseItem::Type)
    {
      this->scene()->removeItem(item);
      this->update_attribute_from_widget();
      this->update_point_colors();
      return;
    }
  }

  this->moving_point = nullptr;
}

void CloudCanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
  QGraphicsView::mouseReleaseEvent(event);

  if (this->moving_point)
  {
    this->moving_point->setPen(QPen(Qt::white, 1));
    this->moving_point = nullptr;

    this->update_attribute_from_widget();
  }
}

void CloudCanvasWidget::update_attribute_from_widget()
{
  QList<QGraphicsItem *> items = this->scene()->items();

  std::vector<hmap::Point> points = {};

  for (QGraphicsItem *item : items)
    if (item->type() == QGraphicsEllipseItem::Type)
    {
      QGraphicsEllipseItem *ellipse_item = dynamic_cast<QGraphicsEllipseItem *>(item);
      if (ellipse_item)
      {
        QPointF position = qgraphicsitem_relative_coordinates(ellipse_item, this);

        float x = (position.x() - margin) / (float)this->width();
        float y = 1.f - (position.y() - margin) / (float)this->height();

        points.push_back(hmap::Point(x, y, item->data(this->id_point_data).toFloat()));
      }
    }

  std::reverse(points.begin(), points.end());

  this->p_attr->set_value(hmap::Cloud(points));

  Q_EMIT this->value_changed();
}

void CloudCanvasWidget::update_point_colors()
{
  float vmin = this->p_attr->get_value().get_values_min();
  float vmax = this->p_attr->get_value().get_values_max();

  for (QGraphicsItem *item : this->scene()->items())
    if (QGraphicsEllipseItem *ellipse_item = dynamic_cast<QGraphicsEllipseItem *>(item))
    {
      float t = (ellipse_item->data(this->id_point_data).toFloat() - vmin) /
                (vmax - vmin);

      float r = t * (1.f - t);
      float g = t * t;
      float b = t;

      QColor color = QColor(static_cast<int>(r * 255),
                            static_cast<int>(g * 255),
                            static_cast<int>(b * 255));

      ellipse_item->setBrush(color);
    }
}

void CloudCanvasWidget::update_scene()
{
  this->clear_scene();
  QPointF global_view_pos = this->mapToGlobal(QPoint(0, 0));

  for (auto &p : this->p_attr->get_value().points)
  {
    QPointF pos = QPointF(margin + p.x * this->width() + global_view_pos.x(),
                          margin + (1.f - p.y) * this->height() + global_view_pos.y());

    this->add_point(pos, p.v);
  }
}

void CloudCanvasWidget::wheelEvent(QWheelEvent *event)
{
  QPointF        scene_pos = this->mapToScene(event->position().toPoint());
  QGraphicsItem *item = this->scene()->itemAt(scene_pos, QTransform());

  if (item && item->type() == QGraphicsEllipseItem::Type)
    if (QGraphicsEllipseItem *ellipse_item = dynamic_cast<QGraphicsEllipseItem *>(item))
    {
      float delta = 0.01f;

      if (event->angleDelta().y() > 0)
        ellipse_item->setData(this->id_point_data,
                              ellipse_item->data(this->id_point_data).toFloat() + delta);
      else
        ellipse_item->setData(this->id_point_data,
                              ellipse_item->data(this->id_point_data).toFloat() - delta);

      this->update_attribute_from_widget();

      this->update_point_colors();
    }
}

} // namespace attr
