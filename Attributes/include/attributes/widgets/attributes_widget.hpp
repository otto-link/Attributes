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
                   std::vector<std::string> *p_attr_ordered_key = nullptr,
                   const std::string        &widget_title = "",
                   const bool                add_save_reset_state_buttons = false);

public Q_SLOTS:
  void on_load_preset();
  void on_restore_initial_state();
  void on_restore_save_state();
  void on_save_state();
  void on_save_preset();

Q_SIGNALS:
  void update_button_released();
  void value_changed();

private:
  std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map;
  std::vector<std::string>                                  *p_attr_ordered_key;

  std::map<std::string, AbstractWidget *> widget_map = {};
};

AbstractWidget *get_attribute_widget(AbstractAttribute *p_attr);

} // namespace attr