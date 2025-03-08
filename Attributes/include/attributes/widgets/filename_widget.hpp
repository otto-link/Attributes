/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file filename_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QPushButton>

#include "attributes/filename_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class FilenameWidget : public AbstractWidget
{
public:
  FilenameWidget() = delete;

  FilenameWidget(FilenameAttribute *p_attr);

  void reset_value() override;

private:
  FilenameAttribute *p_attr;

  QPushButton *button;

  void update_attribute_from_widget();
};

} // namespace attr
