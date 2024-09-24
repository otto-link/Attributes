/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QLabel>

#include "attributes/color_attribute.hpp"

namespace attr
{

class ColorWidget : public QWidget
{
  Q_OBJECT

public:
  ColorWidget() = delete;

  ColorWidget(ColorAttribute *p_attr);

Q_SIGNALS:
  void value_changed();

private:
  ColorAttribute *p_attr;

  QLabel *label;

  void update_attribute_from_widget(QColor color);
};

} // namespace attr
