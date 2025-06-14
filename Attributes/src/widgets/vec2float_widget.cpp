/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with * this
 * software. */

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>

#include "attributes/widgets/vec2float_widget.hpp"

namespace attr
{

XYWidget::XYWidget(Vec2FloatAttribute *p_attr) : p_attr(p_attr)
{
  this->setMinimumSize(100, 100);
  this->set_point(p_attr->get_value()[0], p_attr->get_value()[1]);
}

void XYWidget::center_point()
{
  float x = 0.5f * (this->p_attr->get_xmin() + this->p_attr->get_xmax());
  float y = 0.5f * (this->p_attr->get_ymin() + this->p_attr->get_ymax());
  this->set_point(x, y);
  this->update_attribute_from_widget();
}

void XYWidget::random_point()
{
  uint seed = (uint)time(NULL);

  std::mt19937                          gen(seed);
  std::uniform_real_distribution<float> dis(0.f, 1.f);

  float x = this->p_attr->get_xmin() +
            dis(gen) * (this->p_attr->get_xmax() - this->p_attr->get_xmin());
  float y = this->p_attr->get_ymin() +
            dis(gen) * (this->p_attr->get_ymax() - this->p_attr->get_ymin());

  this->set_point(x, y);
  this->update_attribute_from_widget();
}

void XYWidget::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QRect rect(0.f, 0.f, this->width(), this->height());
  painter.drawRect(rect);

  painter.setPen(QPen(Qt::DotLine));
  rect = QRect(0.5f * margin,
               0.5f * margin,
               this->width() - margin,
               this->height() - margin);
  painter.drawRect(rect);

  // Draw point at the vector's position
  QPointF mapped_point = map_to_widget(this->point);

  painter.setPen(QPen(Qt::SolidLine));
  painter.setBrush(Qt::gray);
  painter.drawEllipse(mapped_point, radius, radius);

  // display value
  QFont font = painter.font();
  font.setPointSize(font.pointSize() - 2);
  painter.setFont(font);

  int dx = (int)(0.25f * margin);
  int dy = (int)(0.1f * margin);
  painter.drawText(QPoint(dx, this->height() - dy), this->p_attr->to_string().c_str());
}

void XYWidget::mousePressEvent(QMouseEvent *event)
{
  this->handle_mouse_event(event->pos());
}

void XYWidget::mouseMoveEvent(QMouseEvent *event)
{
  this->handle_mouse_event(event->pos());
}

void XYWidget::mouseReleaseEvent(QMouseEvent *event)
{
  this->handle_mouse_event(event->pos());
  this->update_attribute_from_widget();
}

void XYWidget::handle_mouse_event(const QPoint &widget_point)
{
  this->point = this->map_to_value(widget_point);
  this->update();
}

QPointF XYWidget::map_to_value(const QPointF &widget_point)
{
  float x = this->p_attr->get_xmin() +
            (widget_point.x() - margin) / (this->width() - margin) *
                (this->p_attr->get_xmax() - this->p_attr->get_xmin());
  float y = this->p_attr->get_ymax() -
            (widget_point.y() - margin) / (this->height() - margin) *
                (this->p_attr->get_ymax() - this->p_attr->get_ymin());

  x = std::clamp(x, this->p_attr->get_xmin(), this->p_attr->get_xmax());
  y = std::clamp(y, this->p_attr->get_ymin(), this->p_attr->get_ymax());

  return QPointF(x, y);
}

QPointF XYWidget::map_to_widget(const QPointF &value_point)
{
  float x = 2.f * radius + (value_point.x() - this->p_attr->get_xmin()) /
                               (this->p_attr->get_xmax() - this->p_attr->get_xmin()) *
                               (this->width() - margin);
  float y = 2.f * radius + (this->p_attr->get_ymax() - value_point.y()) /
                               (this->p_attr->get_ymax() - this->p_attr->get_ymin()) *
                               (this->height() - margin);
  return QPointF(x, y);
}

void XYWidget::set_point(float x, float y)
{
  this->point = QPointF(x, y);
  this->update();
}

void XYWidget::update_attribute_from_widget()
{
  float xf = (float)this->point.x();
  float yf = (float)this->point.y();

  std::vector<float> vec = std::vector<float>({xf, yf});
  this->p_attr->set_value(vec);

  Q_EMIT this->value_changed();
}

Vec2FloatWidget::Vec2FloatWidget(Vec2FloatAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 2);
  }

  // XY selection
  this->xy_widget = new XYWidget(p_attr);
  layout->addWidget((QWidget *)this->xy_widget, row++, 0, 1, 2);

  this->connect(this->xy_widget,
                &XYWidget::value_changed,
                this,
                &Vec2FloatWidget::value_changed);

  // center button
  {
    QPushButton *button = new QPushButton("Center");
    layout->addWidget(button, row, 0);

    this->connect(button,
                  &QPushButton::pressed,
                  this->xy_widget,
                  &XYWidget::center_point);
  }

  // randomize button
  {
    QPushButton *button = new QPushButton("Random");
    layout->addWidget(button, row, 1);

    this->connect(button,
                  &QPushButton::pressed,
                  this->xy_widget,
                  &XYWidget::random_point);
  }

  this->setLayout(layout);
}

void Vec2FloatWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->xy_widget->set_point(p_attr->get_value()[0], p_attr->get_value()[1]);
  this->xy_widget->update();
}

} // namespace attr
