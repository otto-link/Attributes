/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/range_attribute.hpp"

namespace attr
{

RangeAttribute::RangeAttribute()
    : AbstractAttribute(AttributeType::RANGE, "Range", BoundCheck::UPPER_LOWER),
      value({0.f, 1.f}), vmin(-1.f), vmax(2.f), is_active(true)
{
}

RangeAttribute::RangeAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::RANGE, label, BoundCheck::UPPER_LOWER),
      value({0.f, 1.f}), vmin(-1.f), vmax(2.f), is_active(true)
{
}

RangeAttribute::RangeAttribute(std::vector<float> value,
                               float              vmin,
                               float              vmax,
                               const std::string &label,
                               bool               is_active,
                               const BoundCheck  &bound_check)
    : AbstractAttribute(AttributeType::RANGE, label, bound_check), value(value),
      vmin(vmin), vmax(vmax), is_active(is_active)
{
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
