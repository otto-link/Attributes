/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/enum_attribute.hpp"

namespace attr
{

EnumAttribute::EnumAttribute(const std::string                &label,
                             const std::map<std::string, int> &map)
    : AbstractAttribute(AttributeType::ENUM, label), map(map)
{
  this->choice = map.begin()->first;
  this->value = map.begin()->second;

  this->save_state();
  this->save_initial_state();
}

EnumAttribute::EnumAttribute(const std::string                &label,
                             const std::map<std::string, int> &map,
                             const std::string                &choice)
    : AbstractAttribute(AttributeType::ENUM, label), choice(choice), map(map)
{
  auto it = this->map.find(this->choice);

  if (it != this->map.end())
    this->value = it->second;
  else
  {
    this->choice = map.begin()->first;
    this->value = map.begin()->second;
    Logger::log()->warn(
        "Warning: input choice not found in the map, default value set to 0 "
        "(choice: {}).",
        this->choice);
  }

  this->save_state();
  this->save_initial_state();
}

void EnumAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->choice = json["choice"];
}

nlohmann::json EnumAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["choice"] = this->choice;
  return json;
}

} // namespace attr
