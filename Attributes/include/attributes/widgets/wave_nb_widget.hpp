/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec2float_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QPushButton>

#include "doubleslider.hpp"

#include "attributes/wave_nb_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class WaveNbWidget : public AbstractWidget
{
public:
  WaveNbWidget() = delete;

  WaveNbWidget(WaveNbAttribute *p_attr);

  void reset_value() override;

protected Q_SLOTS:

  void on_link_xy_state_change();

  void on_reset();

private:
  WaveNbAttribute *p_attr;

  ValueSliders::DoubleSlider *slider_x;
  ValueSliders::DoubleSlider *slider_y;

  QPushButton *button_link_xy;
  QPushButton *button_reset;

  std::vector<float> value_bckp;

  void update_attribute_from_widget();
};

} // namespace attr
