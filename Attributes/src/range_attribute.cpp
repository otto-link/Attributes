/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/range_attribute.hpp"

namespace attr
{

RangeAttribute::RangeAttribute()
    : AbstractAttribute(AttributeType::RANGE, "Range"), value({0.f, 1.f}), vmin(-1.f),
      vmax(2.f), is_active(true)
{
  this->save_state();
}

RangeAttribute::RangeAttribute(const std::string &label, const bool is_active)
    : AbstractAttribute(AttributeType::RANGE, label), value({0.f, 1.f}), vmin(-1.f),
      vmax(2.f), is_active(is_active)
{
  this->save_state();
}

RangeAttribute::RangeAttribute(const std::string        &label,
                               const std::vector<float> &value,
                               const float               vmin,
                               const float               vmax,
                               const bool                is_active)
    : AbstractAttribute(AttributeType::RANGE, label), value(value), vmin(vmin),
      vmax(vmax), is_active(is_active)
{
  this->save_state();
}

void RangeAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
  this->is_active = json["is_active"];
}

nlohmann::json RangeAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  json["is_active"] = this->is_active;
  return json;
}

std::string RangeAttribute::to_string()
{
  std::string str = "{";
  str += std::to_string(this->value[0]);
  str += ", ";
  str += std::to_string(this->value[1]);
  str += "}";
  return str;
}

} // namespace attr
