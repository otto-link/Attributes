/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>

#include "attributes/widgets/cloud_widget.hpp"

namespace attr
{

CloudCanvasWidget::CloudCanvasWidget(CloudAttribute *p_attr, QWidget *parent)
    : QWidget(parent), p_attr(p_attr), margin(CANVAS_MARGIN), radius(CANVAS_POINT_RADIUS)
{
  int width = CANVAS_WIDTH;

  this->setMinimumSize(QSize(width, width));
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setMouseTracking(true);

  this->update_widget_from_attribute();
}

void CloudCanvasWidget::clear()
{
  this->qpoints.clear();
  this->qvalues.clear();
  this->update();
  this->update_attribute_from_widget();
}

int CloudCanvasWidget::get_hovered_point_index(const QPointF &pos)
{
  for (size_t k = 0; k < this->qpoints.size(); k++)
  {
    QRectF rect(this->qpoints[k].x() - this->radius,
                this->qpoints[k].y() - this->radius,
                2.f * this->radius,
                2.f * this->radius);
    if (rect.contains(pos))
      return static_cast<int>(k);
  }

  return -1;
}

void CloudCanvasWidget::load_from_csv()
{
  QString fname = QFileDialog::getOpenFileName(this, "", "", "CSV file (*.csv)");

  if (!fname.isNull() && !fname.isEmpty())
  {
    this->p_attr->get_value_ref()->from_csv(fname.toStdString());
    this->update_widget_from_attribute();
    this->update();
  }
}

QPointF CloudCanvasWidget::map_to_value(const QPointF &widget_point)
{
  float x = (widget_point.x() - margin) / (this->width() - 2.f * margin);
  float y = 1.f - (widget_point.y() - margin) / (this->height() - 2.f * margin);

  x = std::clamp(x, 0.f, 1.f);
  y = std::clamp(y, 0.f, 1.f);

  return QPointF(x, y);
}

QPointF CloudCanvasWidget::map_to_widget(const QPointF &value_point)
{
  float x = margin + value_point.x() * (this->width() - 2.f * margin);
  float y = margin + (1.f - value_point.y()) * (this->height() - 2.f * margin);
  return QPointF(x, y);
}

void CloudCanvasWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  int index = this->get_hovered_point_index(event->position());

  if (index == -1) // no point hovered
  {
    float cx = std::clamp((float)event->position().x(),
                          this->margin,
                          this->width() - this->margin);
    float cy = std::clamp((float)event->position().y(),
                          this->margin,
                          this->width() - this->margin);

    this->qpoints.push_back(QPointF(cx, cy));
    this->qvalues.push_back(1.f);
    this->update();
    this->update_attribute_from_widget();
  }
}

void CloudCanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (this->moving_point_index != -1)
  {
    // clamp position
    float cx = std::clamp((float)event->position().x(),
                          this->margin,
                          this->width() - this->margin);
    float cy = std::clamp((float)event->position().y(),
                          this->margin,
                          this->width() - this->margin);

    this->qpoints[this->moving_point_index] = QPointF(cx, cy);
    this->update();
  }
}

void CloudCanvasWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    this->moving_point_index = this->get_hovered_point_index(event->position());
  }
  else if (event->button() == Qt::RightButton)
  {
    int index = this->get_hovered_point_index(event->position());
    if (index >= 0)
    {
      this->qpoints.erase(this->qpoints.begin() + index);
      this->qvalues.erase(this->qvalues.begin() + index);
      this->update();
      this->update_attribute_from_widget();
    }
  }
}

void CloudCanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    if (this->moving_point_index != -1)
    {
      this->moving_point_index = -1;
      this->update_attribute_from_widget();
    }
  }
}

void CloudCanvasWidget::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // background
  painter.setBrush(QBrush(CANVAS_BGCOLOR));
  painter.setPen(Qt::black);
  painter.drawRoundedRect(this->rect(), this->radius, this->radius);

  // domain limit
  QPen pen;
  pen.setBrush(Qt::gray);
  pen.setStyle(Qt::DotLine);

  painter.setPen(pen);
  QRect rect(margin, margin, this->width() - 2.f * margin, this->height() - 2.f * margin);
  painter.drawRect(rect);

  // draw points
  pen.setStyle(Qt::SolidLine);
  pen.setBrush(Qt::white);
  painter.setPen(pen);

  for (size_t k = 0; k < this->qpoints.size(); k++)
    painter.drawEllipse(this->qpoints[k], radius, radius);

  // add inner ellipse based on the value associated to the point
  if (this->qpoints.size() > 0)
  {
    float vmin = this->p_attr->get_value_ref()->get_values_min();
    float vmax = this->p_attr->get_value_ref()->get_values_max();
    float inv_vptp = vmin == vmax ? 0.f : 1.f / (vmax - vmin);

    painter.setBrush(QBrush(Qt::darkGray));
    painter.setPen(Qt::NoPen);

    for (size_t k = 0; k < this->qpoints.size(); k++)
    {
      float t = (this->qvalues[k] - vmin) * inv_vptp;
      painter.drawEllipse(this->qpoints[k], 0.9f * t * radius, 0.9f * t * radius);
    }
  }
}

void CloudCanvasWidget::randomize()
{
  if (this->p_attr->get_value_ref()->get_npoints())
  {
    this->p_attr->get_value_ref()->randomize((uint)time(NULL));
    this->update_widget_from_attribute();
    this->update();
    Q_EMIT this->value_changed();
  }
}

void CloudCanvasWidget::update_attribute_from_widget()
{
  std::vector<float> x, y, v;

  for (size_t k = 0; k < this->qpoints.size(); k++)
  {
    QPointF vp = this->map_to_value(this->qpoints[k]);

    x.push_back(static_cast<float>(vp.x()));
    y.push_back(static_cast<float>(vp.y()));
    v.push_back(this->qvalues[k]);
  }

  this->p_attr->set_value(hmap::Cloud(x, y, v));

  Q_EMIT this->value_changed();
}

void CloudCanvasWidget::update_widget_from_attribute()
{
  this->qpoints.clear();
  this->qvalues.clear();

  for (auto &p : this->p_attr->get_value_ref()->points)
  {
    QPointF pos = this->map_to_widget(QPointF(p.x, p.y));
    this->qpoints.push_back(pos);
    this->qvalues.push_back(p.v);
  }
}

void CloudCanvasWidget::wheelEvent(QWheelEvent *event)
{
  int index = this->get_hovered_point_index(event->position());

  if (index >= 0)
  {
    float delta = event->angleDelta().y() > 0 ? 0.01f : -0.01f;
    this->qvalues[index] += delta;

    this->update_attribute_from_widget();
    this->update();
  }
}

} // namespace attr
