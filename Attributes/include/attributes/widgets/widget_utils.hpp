/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QLayout>

namespace attr
{

void setup_default_layout_spacing(QLayout *layout);
void setup_default_layout_spacing(QVBoxLayout *layout);
void setup_default_layout_spacing(QHBoxLayout *layout);
void setup_default_layout_spacing(QGridLayout *layout);

} // namespace attr