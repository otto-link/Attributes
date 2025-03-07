/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file choice_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QRadioButton>

#include "attributes/choice_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class ChoiceWidget : public AbstractWidget
{
public:
  ChoiceWidget() = delete;

  ChoiceWidget(ChoiceAttribute *p_attr);

  void reset_value() override;

private:
  ChoiceAttribute            *p_attr;
  std::vector<QRadioButton *> button_list;

  void update_attribute_from_widget(const std::string &new_value);
};

} // namespace attr
