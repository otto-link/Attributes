/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file range_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QPushButton>

#include "doubleslider.hpp"

#include "attributes/helpers.hpp"
#include "attributes/range_attribute.hpp"

namespace attr
{

class RangeWidget : public QWidget
{
  Q_OBJECT

public:
  RangeWidget() = delete;

  RangeWidget(RangeAttribute *p_attr);

Q_SIGNALS:
  void value_changed();

protected Q_SLOTS:

  void on_active_state_change();

  void on_center();

  void on_reset();

private:
  RangeAttribute *p_attr;

  ValueSliders::DoubleSlider *slider_min;
  ValueSliders::DoubleSlider *slider_max;

  QPushButton *button_active;
  QPushButton *button_center;
  QPushButton *button_reset;

  std::vector<float> value_bckp;

  void update_attribute_from_widget();
};

} // namespace attr
