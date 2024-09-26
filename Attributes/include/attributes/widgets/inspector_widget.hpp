/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file inspector_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QWidget>

#include "attributes/abstract_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class InspectorWidget : public QWidget
{
public:
  InspectorWidget() = delete;

  InspectorWidget(std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map);

private:
  std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map;
};

} // namespace attr