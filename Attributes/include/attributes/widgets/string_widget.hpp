/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QLineEdit>

#include "attributes/string_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// StringWidget
// =====================================

class StringWidget : public AbstractWidget
{
public:
  StringWidget() = delete;
  StringWidget(StringAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  StringAttribute *p_attr;
  QLineEdit       *line_edit;
};

} // namespace attr
