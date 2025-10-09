/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/vec_float_attribute.hpp"

namespace attr
{

VecFloatAttribute::VecFloatAttribute(const std::string        &label,
                                     const std::vector<float> &value,
                                     const float               vmin,
                                     const float               vmax)
    : AbstractAttribute(AttributeType::VEC_FLOAT, label), value(value), vmin(vmin),
      vmax(vmax)
{
  this->save_state();
  this->save_initial_state();
}

void VecFloatAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

std::vector<float> VecFloatAttribute::get_value() const { return this->value; }

std::vector<float> *VecFloatAttribute::get_value_ref() { return &this->value; }

float VecFloatAttribute::get_vmin() const { return this->vmin; }

float VecFloatAttribute::get_vmax() const { return this->vmax; }

nlohmann::json VecFloatAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

void VecFloatAttribute::set_value(const std::vector<float> &new_value)
{
  this->value = new_value;
}

std::string VecFloatAttribute::to_string()
{
  std::string str = "";
  for (auto &v : this->value)
    str += std::to_string(v) + "; ";
  return str;
}

} // namespace attr
