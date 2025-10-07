/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QHBoxLayout>

#include "qsx/slider_int.hpp"

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
  void update_attribute_from_widget();

  IntAttribute   *p_attr;
  qsx::SliderInt *slider;
};

} // namespace attr
