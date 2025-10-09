/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QPushButton>

#include "attributes/filename_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// FilenameWidget
// =====================================

class FilenameWidget : public AbstractWidget
{
public:
  FilenameWidget() = delete;

  FilenameWidget(FilenameAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void update_attribute_from_widget();

  FilenameAttribute *p_attr;
  QPushButton       *button;
};

} // namespace attr
