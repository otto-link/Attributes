/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "qsx/color_gradient_picker.hpp"

#include "attributes/color_gradient_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// ColorGradientWidget
// =====================================

class ColorGradientWidget : public AbstractWidget
{
public:
  ColorGradientWidget() = delete;
  ColorGradientWidget(ColorGradientAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void on_import();
  void on_export();
  void on_shuffle();
  void update_attribute_from_widget();
  void update_widget_from_attribute();

  ColorGradientAttribute   *p_attr;
  qsx::ColorGradientPicker *picker;
};

} // namespace attr
