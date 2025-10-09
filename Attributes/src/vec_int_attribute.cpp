/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/vec_int_attribute.hpp"

namespace attr
{

VecIntAttribute::VecIntAttribute(const std::string      &label,
                                 const std::vector<int> &value,
                                 const int               vmin,
                                 const int               vmax)
    : AbstractAttribute(AttributeType::VEC_INT, label), value(value), vmin(vmin),
      vmax(vmax)
{
  this->save_state();
  this->save_initial_state();
}

std::vector<int> VecIntAttribute::get_value() const { return this->value; }

std::vector<int> *VecIntAttribute::get_value_ref() { return &this->value; }

int VecIntAttribute::get_vmin() const { return this->vmin; }

int VecIntAttribute::get_vmax() const { return this->vmax; }

void VecIntAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<int>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

nlohmann::json VecIntAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

void VecIntAttribute::set_value(const std::vector<int> &new_value)
{
  this->value = new_value;
}

std::string VecIntAttribute::to_string()
{
  std::string str = "";
  for (auto &v : this->value)
    str += std::to_string(v) + "; ";
  return str;
}

} // namespace attr
