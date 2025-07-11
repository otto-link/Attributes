/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QGraphicsBlurEffect>
#include <QMouseEvent>
#include <QPainter>

#include "highmap/range.hpp"

#include "attributes/widgets/array_widget.hpp"

namespace attr
{

ArrayCanvasWidget::ArrayCanvasWidget(QWidget *parent)
    : QWidget(parent), brush_color(Qt::white), brush_radius(64), brush_intensity(0.1f),
      kernel_type(BrushKernel::CUBIC_PULSE)
{
  // initialize the canvas as a black image
  this->image = QImage(DEFAULT_CANVAS_RESOLUTION,
                       DEFAULT_CANVAS_RESOLUTION,
                       QImage::Format_RGB32);
  this->image.fill(Qt::black);
  this->setMouseTracking(true);
  this->setFocusPolicy(Qt::ClickFocus);

  this->setMinimumSize(QSize(CANVAS_WIDTH, CANVAS_WIDTH));
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  this->update_brush_kernel();
}

void ArrayCanvasWidget::clear()
{
  this->image.fill(Qt::black);
  this->update();
  Q_EMIT this->edit_ended(&this->image);
}

void ArrayCanvasWidget::draw_at(const QPoint &pos)
{
  // rescale coordinates based on the current image size on screen
  float dx = pos.x() - this->image_rect.topLeft().x();
  float dy = pos.y() - this->image_rect.topLeft().y();

  int ic = (int)(dx / this->image_rect.width() * this->image.width());
  int jc = (int)(dy / this->image_rect.height() * this->image.height());

  int nk = this->brush_radius;

  if (this->smoothing)
  {
    // apply an average filter on the brush region, intensity of the
    // averaging is locally weighted by the kernel value
    int navg = 5; //(int)(0.25f * this->brush_radius);

    for (int p = -nk; p < nk + 1; p++)
      for (int q = -nk; q < nk + 1; q++)
      {
        if (ic + p >= 0 && ic + p < this->image.width() && jc + q >= 0 &&
            jc + q < this->image.height())
        {
          float value_bckp = this->image.pixelColor(ic + p, jc + q).redF();

          // averaging
          float sum = 0.f;
          int   ns = 0;

          for (int r = -navg; r < navg + 1; r++)
            for (int s = -navg; s < navg + 1; s++)
              if (ic + p + r >= 0 && ic + p + r < this->image.width() &&
                  jc + q + s >= 0 && jc + q + s < this->image.height())
              {
                float v = this->image.pixelColor(ic + p + r, jc + q + s).redF();
                sum += v;
                ns++;
              }

          float t = this->kernel(p + nk, q + nk);
          float value_avg = std::clamp(sum / (float)ns, 0.f, 1.f);
          float value = (1.f - t) * value_bckp + t * value_avg;

          QColor color;
          color.setRgbF(value, value, value);

          this->image.setPixelColor(ic + p, jc + q, color);
        }
      }
  }
  else
  {
    // apply "standard" kernel add
    for (int p = -nk; p < nk + 1; p++)
      for (int q = -nk; q < nk + 1; q++)
      {
        if (ic + p >= 0 && ic + p < this->image.width() && jc + q >= 0 &&
            jc + q < this->image.height())
        {
          // get current value and apply kernel
          float value = this->image.pixelColor(ic + p, jc + q).redF();

          if (this->left_clicking)
          {
            if (this->blending_add)
            {
              // reduce intensity when getting close to value saturation
              float amp = this->brush_intensity * (1.f - value);
              value += amp * this->kernel(p + nk, q + nk);
            }
            else if (this->blending_max)
            {
              value = hmap::maximum_smooth(value,
                                           this->brush_intensity *
                                               this->kernel(p + nk, q + nk),
                                           0.1f);
            }
          }
          else
            value -= this->brush_intensity * this->kernel(p + nk, q + nk);

          value = std::clamp(value, 0.f, 1.f);

          QColor color;
          color.setRgbF(value, value, value);

          this->image.setPixelColor(ic + p, jc + q, color);
        }
      }
  }

  this->update();
}

void ArrayCanvasWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Shift)
  {
    this->blending_add = false;
    this->blending_max = false;
    this->smoothing = true;
  }
  else if (event->key() == Qt::Key_Control)
  {
    this->blending_add = false;
    this->blending_max = true;
    this->smoothing = false;
  }

  this->update();

  QWidget::keyPressEvent(event);
}

void ArrayCanvasWidget::keyReleaseEvent(QKeyEvent *event)
{
  this->blending_add = true;
  this->blending_max = false;
  this->smoothing = false;

  this->update();

  QWidget::keyReleaseEvent(event);
}

void ArrayCanvasWidget::mouseMoveEvent(QMouseEvent *event)
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

void ArrayCanvasWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    this->left_clicking = true;
    this->draw_at(event->pos());
  }
  else if (event->button() == Qt::RightButton)
  {
    this->left_clicking = false;
    this->draw_at(event->pos());
  }
}

void ArrayCanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    Q_EMIT this->edit_ended(&this->image);
}

void ArrayCanvasWidget::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  // painter.drawImage(0, 0, this->image);

  // scale the image to fit within the widget's size, maintaining aspect ratio
  QImage scaled_image = this->image.scaled(this->size(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
  QPoint top_left((width() - scaled_image.width()) / 2,
                  (height() - scaled_image.height()) / 2);
  painter.drawImage(top_left, scaled_image);

  // update current image rectangle
  this->image_rect = QRect(top_left, scaled_image.size());

  // if the mouse is inside the widget, draw the brush circle
  QPoint local_pos = this->mapFromGlobal(QCursor::pos());

  // If the mouse is inside the widget, draw the brush circle
  if (rect().contains(local_pos))
  {
    QPen pen;

    if (this->blending_max)
      pen.setColor(Qt::blue);
    else if (this->smoothing)
      pen.setColor(Qt::red);
    else
      pen.setColor(Qt::green);

    // adjust brush radius to the actual image size as rendered
    int radius = this->brush_radius * this->image_rect.width() / this->image.width();

    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(local_pos, radius, radius);
  }
}

void ArrayCanvasWidget::set_brush_radius(int new_brush_radius)
{
  this->brush_radius = new_brush_radius;
  this->update_brush_kernel();
  this->update();
}

void ArrayCanvasWidget::set_image(const QImage &new_image)
{
  // rescale image to the canvas size
  QSize  size = QSize(DEFAULT_CANVAS_RESOLUTION, DEFAULT_CANVAS_RESOLUTION);
  QImage scaled_image = new_image.scaled(size);
  this->image = scaled_image;
}

void ArrayCanvasWidget::set_kernel_type(const BrushKernel &new_kernel_type)
{
  this->kernel_type = new_kernel_type;
  this->update_brush_kernel();
  this->update();
}

void ArrayCanvasWidget::update_brush_kernel()
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

void ArrayCanvasWidget::wheelEvent(QWheelEvent *event)
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
