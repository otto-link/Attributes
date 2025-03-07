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
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class AttributesWidget : public QWidget
{
  Q_OBJECT

public:
  AttributesWidget() = delete;

  AttributesWidget(std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map,
                   std::vector<std::string> *p_attr_ordered_key = nullptr);

public Q_SLOTS:
  void on_reset_button_released();

Q_SIGNALS:
  void value_changed();

  void update_button_released();

private:
  std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map;
  std::vector<std::string>                                  *p_attr_ordered_key;

  std::vector<AbstractWidget *> widget_list = {};
};

AbstractWidget *get_attribute_widget(AbstractAttribute *p_attr);

} // namespace attr