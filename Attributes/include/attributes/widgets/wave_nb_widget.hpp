/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QPushButton>

#include "qsx/slider_float.hpp"

#include "attributes/wave_nb_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// WaveNbWidget
// =====================================

class WaveNbWidget : public AbstractWidget
{
public:
  WaveNbWidget() = delete;
  WaveNbWidget(WaveNbAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

protected slots:
  void on_link_xy_state_change();
  void on_reset();

private:
  void update_attribute_from_widget();

  WaveNbAttribute   *p_attr;
  qsx::SliderFloat  *slider_x;
  qsx::SliderFloat  *slider_y;
  QPushButton       *button_link_xy;
  QPushButton       *button_reset;
  std::vector<float> value_bckp;
};

} // namespace attr
