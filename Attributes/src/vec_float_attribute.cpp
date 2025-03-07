/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/vec_float_attribute.hpp"

namespace attr
{

VecFloatAttribute::VecFloatAttribute(std::vector<float> value,
                                     float              vmin,
                                     float              vmax,
                                     const std::string &label)
    : AbstractAttribute(AttributeType::VEC_FLOAT, label), value(value), vmin(vmin),
      vmax(vmax)
{
}

void VecFloatAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

nlohmann::json VecFloatAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

std::string VecFloatAttribute::to_string()
{
  std::string str = "";
  for (auto &v : this->value)
    str += std::to_string(v) + "; ";
  return str;
}

} // namespace attr
