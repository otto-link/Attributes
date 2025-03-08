/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file map_enum_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QComboBox>
#include <QHBoxLayout>

#include "attributes/enum_attribute.hpp"
#include "attributes/logger.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class EnumWidget : public AbstractWidget
{
public:
  EnumWidget() = delete;

  EnumWidget(EnumAttribute *p_attr);

  void reset_value();

private:
  EnumAttribute *p_attr;

  QComboBox *combobox;

  void update_attribute_from_widget();
};

} // namespace attr
