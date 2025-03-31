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

StringAttribute::StringAttribute(const std::string &label,
                                 const std::string &value,
                                 bool               read_only)
    : AbstractAttribute(AttributeType::STRING, label), value(value), read_only(read_only)
{
  this->save_state();
}

void StringAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::string>();
  this->read_only = json["read_only"];
}

nlohmann::json StringAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["read_only"] = this->read_only;
  return json;
}

} // namespace attr
