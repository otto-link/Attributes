/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/abstract_attribute.hpp"

namespace attr
{

AbstractAttribute::AbstractAttribute(const AttributeType &type,
                                     const std::string   &label,
                                     const BoundCheck    &bound_check)
    : type(type), label(label), bound_check(bound_check)
{
}

void AbstractAttribute::json_from(nlohmann::json const &json)
{
  this->type = json["type"].get<AttributeType>();
  this->label = json["label"];
  this->bound_check = json["bound_check"].get<BoundCheck>();
}

nlohmann::json AbstractAttribute::json_to() const
{
  nlohmann::json json;
  json["type"] = this->type;
  json["type_string"] = attribute_type_map.at(this->type);
  json["label"] = this->label;
  json["bound_check"] = this->bound_check;
  return json;
}

} // namespace attr
