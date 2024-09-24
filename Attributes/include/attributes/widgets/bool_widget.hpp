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

namespace attr
{

class BoolWidget : public QWidget
{
  Q_OBJECT

public:
  BoolWidget() = delete;

  BoolWidget(BoolAttribute *p_attr);

Q_SIGNALS:
  void value_changed();

private:
  BoolAttribute *p_attr;

  QPushButton *button;

  void update_attribute_from_widget();
};

} // namespace attr
