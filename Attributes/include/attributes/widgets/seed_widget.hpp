/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file seed_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "intslider.hpp"

#include "attributes/seed_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class SeedWidget : public AbstractWidget
{
public:
  SeedWidget() = delete;

  SeedWidget(SeedAttribute *p_attr);

private:
  SeedAttribute *p_attr;

  uint value_bckp;

  ValueSliders::IntSlider *slider;

  void update_attribute_from_widget();
};

} // namespace attr
