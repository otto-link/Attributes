/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/wave_nb_attribute.hpp"

namespace attr
{

WaveNbAttribute::WaveNbAttribute()
    : AbstractAttribute(AttributeType::WAVE_NB, "Wavenumber", BoundCheck::LOWER_ONLY),
      value({2.f, 2.f}), vmin(0.f), vmax(16.f), link_xy(true)
{
}

WaveNbAttribute::WaveNbAttribute(std::vector<float> value,
                                 float              vmin,
                                 float              vmax,
                                 bool               link_xy,
                                 const std::string &label,
                                 const BoundCheck  &bound_check)
    : AbstractAttribute(AttributeType::WAVE_NB, label, bound_check), value(value),
      vmin(vmin), vmax(vmax), link_xy(link_xy)
{
}

void WaveNbAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
  this->link_xy = json["link_xy"];
}

nlohmann::json WaveNbAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  json["link_xy"] = this->link_xy;
  return json;
}

std::string WaveNbAttribute::to_string()
{
  std::string str = "{";

  // Iterate through the vector and concatenate values
  for (size_t i = 0; i < this->value.size(); ++i)
  {
    if (i > 0)
      str += ", ";
    str += std::to_string(this->value[i]);
  }
  return str + "}";
}

} // namespace attr
