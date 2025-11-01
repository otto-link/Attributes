/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QButtonGroup>
#include <QComboBox>
#include <QWidget>

#include "attributes/choice_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class ChoiceWidget : public AbstractWidget
{
public:
  enum class DisplayMode
  {
    COMBO,
    BUTTONS
  };

  ChoiceWidget(ChoiceAttribute *p_attr);

  void reset_value(bool reset_to_initial_state) override;

private:
  void build_combo_ui(QVBoxLayout *layout);
  void build_button_ui(QVBoxLayout *layout);
  void update_attribute_from_widget(const std::string &new_value);

  ChoiceAttribute *p_attr;
  DisplayMode      mode;
  QComboBox       *combobox = nullptr;
  QButtonGroup    *button_group = nullptr;
};

} // namespace attr
