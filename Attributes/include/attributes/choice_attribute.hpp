/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// ChoiceAttribute
// =====================================

class ChoiceAttribute : public AbstractAttribute
{
public:
  ChoiceAttribute(const std::vector<std::string> &choice_list, const std::string &value);
  ChoiceAttribute(const std::string              &label,
                  const std::vector<std::string> &choice_list,
                  const std::string              &value);
  ChoiceAttribute(const std::string &label, const std::vector<std::string> &choice_list);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<std::string> get_choice_list() const;
  bool                     get_use_combo_list() const;
  std::string              get_value() const;
  void        set_choice_list(const std::vector<std::string> &new_choice_list);
  void        set_use_combo_list(bool new_state);
  void        set_value(const std::string &new_value);
  std::string to_string() override;

private:
  std::string              value;
  std::vector<std::string> choice_list;
  bool                     use_combo_list = false; // as opposed to buttons
};

} // namespace attr
