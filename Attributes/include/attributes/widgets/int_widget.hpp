/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file int_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QHBoxLayout>

#include "intslider.hpp"

#include "attributes/int_attribute.hpp"
#include "attributes/logger.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class IntWidget : public AbstractWidget
{
public:
  IntWidget() = delete;

  IntWidget(IntAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  IntAttribute *p_attr;

  ValueSliders::IntSlider *slider;

  void update_attribute_from_widget();
};

} // namespace attr
