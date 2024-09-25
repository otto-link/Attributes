/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file bool_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QPushButton>

#include "attributes/bool_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class BoolWidget : public AbstractWidget
{
public:
  BoolWidget() = delete;

  BoolWidget(BoolAttribute *p_attr);

private:
  BoolAttribute *p_attr;

  QPushButton *button;

  void update_attribute_from_widget();
};

} // namespace attr
