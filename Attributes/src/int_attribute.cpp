/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/int_attribute.hpp"

namespace attr
{

IntAttribute::IntAttribute(const std::string &label, int value, int vmin, int vmax)
    : AbstractAttribute(AttributeType::INT, label), value(value), vmin(vmin), vmax(vmax)
{
  this->save_state();
  this->save_initial_state();
}

void IntAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

nlohmann::json IntAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

} // namespace attr
