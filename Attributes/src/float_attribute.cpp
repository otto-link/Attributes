/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/float_attribute.hpp"

namespace attr
{

FloatAttribute::FloatAttribute(const std::string &label,
                               float              value,
                               float              vmin,
                               float              vmax,
                               std::string        value_format)
    : AbstractAttribute(AttributeType::FLOAT, label), value(value), vmin(vmin),
      vmax(vmax), value_format(value_format)
{
  this->save_state();
  this->save_initial_state();
}

void FloatAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

nlohmann::json FloatAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

} // namespace attr
