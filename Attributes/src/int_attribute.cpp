/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/int_attribute.hpp"

namespace attr
{

IntAttribute::IntAttribute(const std::string &label,
                           int                value,
                           int                vmin,
                           int                vmax,
                           std::string        value_format)
    : AbstractAttribute(AttributeType::INT, label), value(value), vmin(vmin), vmax(vmax),
      value_format(value_format)
{
  this->save_state();
  this->save_initial_state();
}

int IntAttribute::get_value() const { return this->value; }

std::string IntAttribute::get_value_format() const { return this->value_format; }

int IntAttribute::get_vmin() const { return this->vmin; }

int IntAttribute::get_vmax() const { return this->vmax; }

void IntAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get(json, "value", value);
  json_safe_get(json, "vmin", vmin);
  json_safe_get(json, "vmax", vmax);
}

nlohmann::json IntAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

void IntAttribute::set_value(const int &new_value) { this->value = new_value; }

std::string IntAttribute::to_string() { return std::to_string(this->value); }

} // namespace attr
