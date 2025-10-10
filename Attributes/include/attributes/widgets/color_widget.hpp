/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "qsx/color_picker.hpp"

#include "attributes/color_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// ColorWidget
// =====================================

class ColorWidget : public AbstractWidget
{
public:
  ColorWidget() = delete;
  ColorWidget(ColorAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void update_attribute_from_widget();
  void update_widget_from_attribute();

  ColorAttribute   *p_attr;
  qsx::ColorPicker *picker;
};

} // namespace attr
