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
                               std::string        value_format,
                               bool               log_scale)
    : AbstractAttribute(AttributeType::FLOAT, label), value(value), vmin(vmin),
      vmax(vmax), value_format(value_format), log_scale(log_scale)
{
  this->save_state();
  this->save_initial_state();
}

bool FloatAttribute::get_log_scale() const { return this->log_scale; }

float FloatAttribute::get_value() const { return this->value; }

std::string FloatAttribute::get_value_format() const { return this->value_format; }

float FloatAttribute::get_vmin() const { return this->vmin; }

float FloatAttribute::get_vmax() const { return this->vmax; }

void FloatAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get(json, "value", value);
  json_safe_get(json, "vmin", vmin);
  json_safe_get(json, "vmax", vmax);
  json_safe_get(json, "log_scale", log_scale);
}

nlohmann::json FloatAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  json["log_scale"] = this->log_scale;
  return json;
}

void FloatAttribute::set_value(const float &new_value) { this->value = new_value; }

std::string FloatAttribute::to_string() { return std::to_string(this->value); }

} // namespace attr
