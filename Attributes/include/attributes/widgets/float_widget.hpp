/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file float_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "doubleslider.hpp"

#include "attributes/float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class FloatWidget : public AbstractWidget
{
public:
  FloatWidget() = delete;

  FloatWidget(FloatAttribute *p_attr);

  void reset_value() override;

private:
  FloatAttribute *p_attr;

  ValueSliders::DoubleSlider *slider;

  void update_attribute_from_widget();
};

} // namespace attr
