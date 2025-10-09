/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QLabel>

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
  void on_color_pick_button_released();
  void update_attribute_from_widget(const QColor &color);
  void update_label_color();

  ColorAttribute *p_attr;
  QLabel         *label;
};

} // namespace attr
