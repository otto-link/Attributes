/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QMouseEvent>
#include <QPainter>

#include "attributes/widgets/array_widget.hpp"

namespace attr
{

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent), brush_color(Qt::white), brush_radius(64), brush_intensity(0.1f),
      kernel_type(BrushKernel::CUBIC_PULSE)
{
  // initialize the canvas as a black image
  this->image = QImage(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_WIDTH, QImage::Format_RGB32);
  this->image.fill(Qt::black);
  this->setMouseTracking(true);

  this->update_brush_kernel();
}

void CanvasWidget::clear()
{
  this->image.fill(Qt::black);
  this->update();
  Q_EMIT this->edit_ended(&this->image);
}

void CanvasWidget::draw_at(const QPoint &pos)
{
  int ic = pos.x();
  int jc = pos.y();

  int nk = this->brush_radius;

  for (int p = -nk; p < nk + 1; p++)
    for (int q = -nk; q < nk + 1; q++)
    {
      if (ic + p >= 0 && ic + p < this->image.width() && jc + q >= 0 &&
          jc + q < this->image.height())
      {
        // get current value and apply kernel
        float value = this->image.pixelColor(ic + p, jc + q).redF();

        if (this->adding)
        {
          // reduce intensity when getting close to value saturation
          float amp = this->brush_intensity * (1.f - value);
          value += amp * this->kernel(p + nk, q + nk);
        }
        else
          value -= this->brush_intensity * this->kernel(p + nk, q + nk);

        value = std::clamp(value, 0.f, 1.f);

        QColor color;
        color.setRgbF(value, value, value);

        this->image.setPixelColor(ic + p, jc + q, color);
      }
    }
  this->update();
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & (Qt::LeftButton | Qt::RightButton))
  {
    QPointF dp = event->pos() - this->previous_pos;
    float   delta = std::hypot(dp.x(), dp.y());

    // only apply the brush when a minimum distance has been done with the mouse to keep
    // a constant feeling of pressure
    if (delta > 0.1f * this->brush_radius)
    {
      this->draw_at(event->pos());
      this->previous_pos = event->pos();
    }
  }

  this->update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    this->adding = true;
    this->draw_at(event->pos());
  }
  else if (event->button() == Qt::RightButton)
  {
    this->adding = false;
    this->draw_at(event->pos());
  }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
    Q_EMIT this->edit_ended(&this->image);
}

void CanvasWidget::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);
  painter.drawImage(0, 0, this->image);

  // if the mouse is inside the widget, draw the brush circle
  QPoint local_pos = this->mapFromGlobal(QCursor::pos());

  // If the mouse is inside the widget, draw the brush circle
  if (rect().contains(local_pos))
  {
    QPen pen(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(local_pos, this->brush_radius, this->brush_radius);
  }
}

void CanvasWidget::set_brush_radius(int new_brush_radius)
{
  this->brush_radius = new_brush_radius;
  this->update_brush_kernel();
  this->update();
}

void CanvasWidget::set_image(const QImage &new_image)
{
  // rescale image to the canvas size
  QSize  size = QSize(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_WIDTH);
  QImage scaled_image = new_image.scaled(size);
  this->image = scaled_image;
}

void CanvasWidget::set_kernel_type(const BrushKernel &new_kernel_type)
{
  this->kernel_type = new_kernel_type;
  this->update_brush_kernel();
  this->update();
}

void CanvasWidget::update_brush_kernel()
{
  hmap::Vec2<int> shape(2 * this->brush_radius + 1, 2 * this->brush_radius + 1);

  if (kernel_type == BrushKernel::CONE)
    this->kernel = hmap::cone(shape);
  else if (kernel_type == BrushKernel::CONE_SMOOTH)
    this->kernel = hmap::cone_smooth(shape);
  else if (kernel_type == BrushKernel::CUBIC_PULSE)
    this->kernel = hmap::cubic_pulse(shape);
  else if (kernel_type == BrushKernel::DISK)
    this->kernel = hmap::disk(shape);

  this->kernel /= this->kernel.max();
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
  if (event->angleDelta().y() > 0)
    this->brush_radius += 1;
  else
    this->brush_radius -= 1;

  this->brush_radius = std::clamp(this->brush_radius, 1, this->image.width());
  this->update_brush_kernel();
  this->update();
}

} // namespace attr
