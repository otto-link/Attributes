/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

void setup_default_layout_spacing(QLayout *layout)
{
  layout->setSpacing(1);
  layout->setContentsMargins(0, 0, 0, 0);
}

void setup_default_layout_spacing(QVBoxLayout *layout)
{
  if (auto ptr = dynamic_cast<QLayout *>(layout))
    setup_default_layout_spacing(ptr);
}

void setup_default_layout_spacing(QHBoxLayout *layout)
{
  if (auto ptr = dynamic_cast<QLayout *>(layout))
    setup_default_layout_spacing(ptr);
}

void setup_default_layout_spacing(QGridLayout *layout)
{
  if (auto ptr = dynamic_cast<QLayout *>(layout))
    setup_default_layout_spacing(ptr);
}

} // namespace attr
