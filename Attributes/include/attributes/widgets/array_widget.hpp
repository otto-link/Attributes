/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file array_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "highmap/kernels.hpp"

#include "attributes/array_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

#define DEFAULT_CANVAS_WIDTH 512

namespace attr
{

enum BrushKernel
{
  CONE,
  CONE_SMOOTH,
  CUBIC_PULSE,
  DISK,
};

static std::map<std::string, BrushKernel> brush_kernel_map = {
    {"Cone", BrushKernel::CONE},
    {"Cone (smooth)", BrushKernel::CONE_SMOOTH},
    {"Cubic pulse", BrushKernel::CUBIC_PULSE},
    {"Disc", BrushKernel::DISK},
};

class CanvasWidget : public QWidget
{
  Q_OBJECT
public:
  CanvasWidget(QWidget *parent = nullptr);

  void clear();

  float get_brush_intensity() { return this->brush_intensity; }

  QImage *get_image_ref() { return &this->image; }

  void set_brush_intensity(float new_brush_intensity)
  {
    this->brush_intensity = new_brush_intensity;
  }

  void set_brush_radius(int new_brush_radius);

  void set_image(const QImage &new_image);

  void set_kernel_type(const BrushKernel &new_kernel_type);

  QSize sizeHint() const override
  {
    return QSize(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_WIDTH);
  }

  void smooth();

Q_SIGNALS:
  void edit_ended(QImage *p_image);

protected:
  void keyPressEvent(QKeyEvent *event) override;

  void keyReleaseEvent(QKeyEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void update_brush_kernel();

  void wheelEvent(QWheelEvent *event) override;

private:
  QImage image;
  QRect  image_rect;

  QColor      brush_color;
  int         brush_radius;
  float       brush_intensity;
  BrushKernel kernel_type;

  bool left_clicking;

  bool blending_add = true;
  bool blending_max = false;
  bool smoothing = false;

  hmap::Array kernel;

  QPointF previous_pos = QPointF(0.f, 0.f);

  void draw_at(const QPoint &pos);
};

class ArrayWidget : public AbstractWidget
{
  Q_OBJECT

public:
  ArrayWidget() = delete;

  ArrayWidget(ArrayAttribute *p_attr);

public Q_SLOTS:
  void on_canvas_edit_ended(QImage *p_image);

private:
  ArrayAttribute *p_attr;

  CanvasWidget *canvas;

  QImage array_to_image();

  void smooth_array();
};

} // namespace attr
