/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file map_enum_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class MapEnumAttribute : public AbstractAttribute
{
public:
  MapEnumAttribute() = delete;

  MapEnumAttribute(std::map<std::string, int> map, const std::string &label = "");

  MapEnumAttribute(std::string                choice,
                   std::map<std::string, int> map,
                   const std::string         &label = "");

  std::string get_choice() const { return this->choice; }

  int get_value() const { return this->value; }

  std::map<std::string, int> get_map() const { return this->map; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const int &new_value) { this->value = new_value; }

  void set_choice(const std::string &new_choice) { this->choice = new_choice; }

  std::string to_string() { return this->choice; }

private:
  int                        value;
  std::string                choice;
  std::map<std::string, int> map;
};

} // namespace attr
