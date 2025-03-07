/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/abstract_attribute.hpp"

namespace attr
{

AbstractAttribute::AbstractAttribute(const AttributeType &type, const std::string &label)
    : type(type), label(label)
{
}

void AbstractAttribute::json_from(nlohmann::json const &json)
{
  this->type = json["type"].get<AttributeType>();
  this->label = json["label"];
}

nlohmann::json AbstractAttribute::json_to() const
{
  nlohmann::json json;
  json["type"] = this->type;
  json["type_string"] = attribute_type_map.at(this->type);
  json["label"] = this->label;
  return json;
}

void AbstractAttribute::reset_to_save_state()
{
  if (this->attribute_state.is_null())
  {
    Logger::log()->error(
        "empty saved state, could not reset attribute state. attribute label: {}",
        this->label);
  }
  else
    this->json_from(this->attribute_state);
}

void AbstractAttribute::save_state()
{
  // serialize current state
  this->attribute_state = this->json_to();
}

} // namespace attr
