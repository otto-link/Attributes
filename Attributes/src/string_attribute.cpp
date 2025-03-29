/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/string_attribute.hpp"

namespace attr
{

StringAttribute::StringAttribute(const std::string &label, const std::string &value)
    : AbstractAttribute(AttributeType::STRING, label), value(value)
{
  this->save_state();
}

void StringAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::string>();
}

nlohmann::json StringAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  return json;
}

} // namespace attr
