/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once

#include "qsx/slider_int.hpp"

#include "attributes/seed_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// SeedWidget
// =====================================

class SeedWidget : public AbstractWidget
{
public:
  SeedWidget() = delete;
  SeedWidget(SeedAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void update_attribute_from_widget();

  SeedAttribute  *p_attr;
  uint            value_bckp;
  qsx::SliderInt *slider;
};

} // namespace attr
