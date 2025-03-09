/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>

#include "attributes/widgets/vec_int_widget.hpp"

namespace attr
{

// --- base VecWidget

IVecWidget::IVecWidget(VecIntAttribute *p_attr, QWidget *parent)
    : QWidget(parent), p_attr(p_attr), radius(CANVAS_POINT_RADIUS)
{
  this->setMinimumSize(128, 128);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setMouseTracking(true);

  this->update_widget_from_attribute();
}

int IVecWidget::get_hovered_point_index(const QPointF &pos)
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

int IVecWidget::map_ypos_to_value(float ypos)
{
  float v = 1.f - ypos / this->height();
  v = std::clamp(v, 0.f, 1.f);
  return (int)(this->p_attr->get_vmin() +
               v * (this->p_attr->get_vmax() - this->p_attr->get_vmin()));
}

float IVecWidget::map_value_to_ypos(int value)
{
  float ypos = (float)(value - this->p_attr->get_vmin()) /
               (float)(this->p_attr->get_vmax() - this->p_attr->get_vmin());
  return (1.f - ypos) * this->height();
}

void IVecWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (this->moving_point_index != -1)
  {
    // clamp position
    float cx = (float)this->qpoints[this->moving_point_index].x();

    float cy = std::clamp((float)event->position().y(), 0.f, (float)this->height());

    this->qpoints[this->moving_point_index] = QPointF(cx, cy);
    this->update();
  }
}

void IVecWidget::mousePressEvent(QMouseEvent *event)
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
      this->update();
      this->update_attribute_from_widget();
      this->update_widget_from_attribute();
    }
  }
}

void IVecWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    if (this->moving_point_index != -1)
    {
      this->moving_point_index = -1;
      this->update();
      this->update_attribute_from_widget();
    }
  }
}

void IVecWidget::new_value()
{
  int new_value = (int)(0.5f * (this->p_attr->get_vmin() + this->p_attr->get_vmax()));

  // push back last value if one is available
  if (this->p_attr->get_value().size() > 0)
    new_value = this->p_attr->get_value().back();

  this->p_attr->get_value_ref()->push_back(new_value);
  this->update_widget_from_attribute();
  Q_EMIT this->value_changed();
}

void IVecWidget::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // background
  painter.setBrush(QBrush(CANVAS_BGCOLOR));
  painter.setPen(Qt::black);
  painter.drawRoundedRect(this->rect(), this->radius, this->radius);

  // edges
  QPen pen;
  pen.setStyle(Qt::SolidLine);
  pen.setBrush(Qt::darkGray);
  painter.setPen(pen);

  for (auto &qp : this->qpoints)
    painter.drawLine(QPointF(qp.x(), this->height()), qp);

  if (this->qpoints.size() > 1)
    for (size_t k = 0; k < this->qpoints.size() - 1; k++)
      painter.drawLine(this->qpoints[k], this->qpoints[k + 1]);

  // draw points
  pen.setWidth(1);
  painter.setPen(pen);

  painter.setBrush(QBrush(CANVAS_BGCOLOR));
  painter.setPen(Qt::NoPen);
  for (auto &qp : this->qpoints)
    painter.drawEllipse(qp, 1.3f * radius, 1.3f * radius);

  pen.setBrush(Qt::white);
  painter.setPen(pen);

  for (size_t k = 0; k < this->qpoints.size(); k++)
    painter.drawEllipse(this->qpoints[k], radius, radius);

  // display value if moving point
  if (this->moving_point_index >= 0)
  {
    float ypos = (float)this->qpoints[this->moving_point_index].y();
    int   value = this->map_ypos_to_value(ypos);
    painter.drawText(this->qpoints[this->moving_point_index] +
                         QPointF(this->radius, -this->radius),
                     std::to_string(value).c_str());
  }
}

void IVecWidget::update_attribute_from_widget()
{
  std::vector<int> values = {};

  for (auto &qp : this->qpoints)
    values.push_back(this->map_ypos_to_value(qp.y()));

  this->p_attr->set_value(values);

  Q_EMIT this->value_changed();
}

void IVecWidget::update_widget_from_attribute()
{
  this->qpoints.clear();

  int nvalues = (int)this->p_attr->get_value().size();

  for (int k = 0; k < nvalues; k++)
  {
    float x = (float)(k + 1) / (nvalues + 1) * this->width();
    float y = this->map_value_to_ypos(this->p_attr->get_value()[k]);

    this->qpoints.push_back(QPointF(x, y));
  }

  this->update();
}

// --- VecIntWidget

VecIntWidget::VecIntWidget(VecIntAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 2);
  }

  // selection
  this->vec_widget = new IVecWidget(p_attr, this);
  layout->addWidget((QWidget *)this->vec_widget, row++, 0, 1, 2);

  this->connect(this->vec_widget,
                &IVecWidget::value_changed,
                this,
                &VecIntWidget::value_changed);

  // buttons
  {
    QPushButton *button = new QPushButton("New value");
    layout->addWidget(button, row, 0);

    this->connect(button,
                  &QPushButton::pressed,
                  this->vec_widget,
                  &IVecWidget::new_value);
  }

  this->setLayout(layout);
}

void VecIntWidget::reset_value()
{
  this->p_attr->reset_to_save_state();
  this->vec_widget->update_widget_from_attribute();
}

} // namespace attr
