/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QComboBox>
#include <QHBoxLayout>

#include "attributes/enum_attribute.hpp"
#include "attributes/logger.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// EnumWidget
// =====================================

class EnumWidget : public AbstractWidget
{
public:
  EnumWidget() = delete;
  EnumWidget(EnumAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false);

private:
  void update_attribute_from_widget();

  EnumAttribute *p_attr;
  QComboBox     *combobox;
};

} // namespace attr
