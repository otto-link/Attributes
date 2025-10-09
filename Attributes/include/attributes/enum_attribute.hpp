/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// EnumAttribute
// =====================================

class EnumAttribute : public AbstractAttribute
{
public:
  EnumAttribute(const std::string &label, const std::map<std::string, int> &map);
  EnumAttribute(const std::string                &label,
                const std::map<std::string, int> &map,
                const std::string                &choice);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::string                get_choice() const;
  int                        get_value() const;
  std::map<std::string, int> get_map() const;
  void                       set_value(const int &new_value);
  void                       set_choice(const std::string &new_choice);
  std::string                to_string() override;

private:
  int                        value;
  std::string                choice;
  std::map<std::string, int> map;
};

} // namespace attr
