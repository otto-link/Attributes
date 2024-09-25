/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file attributes_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QWidget>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

QWidget *get_attribute_widget(AbstractAttribute *p_attr);

QWidget *get_attribute_widget(std::vector<AbstractAttribute *> p_attributes,
                              const std::string               &label = "",
                              bool                             horizontal_layout = false);

} // namespace attr