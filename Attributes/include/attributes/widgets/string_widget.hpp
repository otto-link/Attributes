/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file string_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QLineEdit>

#include "attributes/string_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class StringWidget : public AbstractWidget
{
public:
  StringWidget() = delete;

  StringWidget(StringAttribute *p_attr);

private:
  StringAttribute *p_attr;

  QLineEdit *line_edit;
};

} // namespace attr
