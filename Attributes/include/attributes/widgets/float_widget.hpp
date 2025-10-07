/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "qsx/slider_float.hpp"

#include "attributes/float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class FloatWidget : public AbstractWidget
{
public:
  FloatWidget() = delete;
  FloatWidget(FloatAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void update_attribute_from_widget();

  FloatAttribute   *p_attr;
  qsx::SliderFloat *slider;
};

} // namespace attr
