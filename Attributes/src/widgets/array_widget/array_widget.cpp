/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <algorithm>
#include <cmath>
#include <vector>

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/array_widget.hpp"
#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

// =====================================
// Local resampling / range helpers
// =====================================

static void remap_to_unit(std::vector<float> &v)
{
  if (v.empty())
    return;
  float mn = *std::min_element(v.begin(), v.end());
  float mx = *std::max_element(v.begin(), v.end());
  float range = mx - mn;
  if (range > 0.f)
    for (auto &x : v)
      x = (x - mn) / range;
}

static std::vector<float> resample_bilinear(const std::vector<float> &src,
                                            int                       src_w,
                                            int                       src_h,
                                            int                       dst_w,
                                            int                       dst_h)
{
  std::vector<float> dst(static_cast<size_t>(dst_w * dst_h));
  const float        x_scale = static_cast<float>(src_w) / static_cast<float>(dst_w);
  const float        y_scale = static_cast<float>(src_h) / static_cast<float>(dst_h);

  for (int j = 0; j < dst_h; ++j)
  {
    for (int i = 0; i < dst_w; ++i)
    {
      const float sx = (i + 0.5f) * x_scale - 0.5f;
      const float sy = (j + 0.5f) * y_scale - 0.5f;

      const int x0 = std::clamp(static_cast<int>(std::floor(sx)), 0, src_w - 1);
      const int x1 = std::clamp(x0 + 1, 0, src_w - 1);
      const int y0 = std::clamp(static_cast<int>(std::floor(sy)), 0, src_h - 1);
      const int y1 = std::clamp(y0 + 1, 0, src_h - 1);

      const float tx = sx - std::floor(sx);
      const float ty = sy - std::floor(sy);

      const float v00 = src[y0 * src_w + x0];
      const float v10 = src[y0 * src_w + x1];
      const float v01 = src[y1 * src_w + x0];
      const float v11 = src[y1 * src_w + x1];

      dst[j * dst_w + i] = (1.f - ty) * ((1.f - tx) * v00 + tx * v10) +
                           ty * ((1.f - tx) * v01 + tx * v11);
    }
  }
  return dst;
}

// Catmull-Rom cubic interpolation along one axis
static float cubic_hermite(float a, float b, float c, float d, float t)
{
  const float A = -0.5f * a + 1.5f * b - 1.5f * c + 0.5f * d;
  const float B = a - 2.5f * b + 2.0f * c - 0.5f * d;
  const float C = -0.5f * a + 0.5f * c;
  const float D = b;
  return ((A * t + B) * t + C) * t + D;
}

static std::vector<float> resample_bicubic(const std::vector<float> &src,
                                           int                       src_w,
                                           int                       src_h,
                                           int                       dst_w,
                                           int                       dst_h)
{
  // clamped accessor
  auto at = [&](int x, int y) -> float
  {
    x = std::clamp(x, 0, src_w - 1);
    y = std::clamp(y, 0, src_h - 1);
    return src[y * src_w + x];
  };

  std::vector<float> dst(static_cast<size_t>(dst_w * dst_h));
  const float        x_scale = static_cast<float>(src_w) / static_cast<float>(dst_w);
  const float        y_scale = static_cast<float>(src_h) / static_cast<float>(dst_h);

  for (int j = 0; j < dst_h; ++j)
  {
    for (int i = 0; i < dst_w; ++i)
    {
      const float sx = (i + 0.5f) * x_scale - 0.5f;
      const float sy = (j + 0.5f) * y_scale - 0.5f;

      const int   x0 = static_cast<int>(std::floor(sx));
      const int   y0 = static_cast<int>(std::floor(sy));
      const float tx = sx - static_cast<float>(x0);
      const float ty = sy - static_cast<float>(y0);

      // interpolate 4 rows along x, then interpolate those along y
      float rows[4];
      for (int r = -1; r <= 2; ++r)
        rows[r + 1] = cubic_hermite(at(x0 - 1, y0 + r),
                                    at(x0, y0 + r),
                                    at(x0 + 1, y0 + r),
                                    at(x0 + 2, y0 + r),
                                    tx);

      dst[j * dst_w + i] = cubic_hermite(rows[0], rows[1], rows[2], rows[3], ty);
    }
  }
  return dst;
}

// =====================================
// ArrayWidget
// =====================================

ArrayWidget::ArrayWidget(ArrayAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  int row = 0;

  this->canvas = new qsx::CanvasField(this->p_attr->get_label().c_str(),
                                      DEFAULT_CANVAS_RESOLUTION,
                                      DEFAULT_CANVAS_RESOLUTION);

  if (this->p_attr->get_background_image_fct())
  {
    QImage bg_image = this->p_attr->get_background_image_fct()();
    this->canvas->set_bg_image(bg_image);
  }

  this->array_data_to_widget_field_data();

  this->connect(this->canvas,
                &qsx::CanvasField::edit_ended,
                this,
                &ArrayWidget::on_canvas_edit_ended);

  layout->addWidget(this->canvas, row, 0);
  row++;

  this->setLayout(layout);
}

void ArrayWidget::array_data_to_widget_field_data()
{
  const glm::ivec2   shape = this->p_attr->get_shape();
  std::vector<float> data = this->p_attr->get_value(); // copy for remapping

  remap_to_unit(data);

  const int cw = this->canvas->get_field_width();
  const int ch = this->canvas->get_field_height();

  data = resample_bilinear(data, shape.x, shape.y, cw, ch);
  this->canvas->set_field_data(data);
}

void ArrayWidget::on_canvas_edit_ended()
{
  const int          cw = this->canvas->get_field_width();
  const int          ch = this->canvas->get_field_height();
  const glm::ivec2   attr_shape = this->p_attr->get_shape();
  std::vector<float> data = this->canvas->get_field_data();

  *this->p_attr->get_value_ref() = resample_bicubic(data,
                                                    cw,
                                                    ch,
                                                    attr_shape.x,
                                                    attr_shape.y);

  Q_EMIT this->value_changed();
}

void ArrayWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->array_data_to_widget_field_data();
  this->canvas->update();
}

} // namespace attr
