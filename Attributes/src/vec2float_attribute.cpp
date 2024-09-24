/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/vec2float_attribute.hpp"

namespace attr
{

Vec2FloatAttribute::Vec2FloatAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::VEC2FLOAT, label, BoundCheck::UNCHECKED),
      value({0.5f, 0.5f}), xmin(0.f), xmax(1.f), ymin(0.f), ymax(1.f)
{
}

Vec2FloatAttribute::Vec2FloatAttribute(std::vector<float> value,
                                       float              xmin,
                                       float              xmax,
                                       float              ymin,
                                       float              ymax,
                                       const std::string &label)
    : AbstractAttribute(AttributeType::VEC2FLOAT, label, BoundCheck::UNCHECKED),
      value(value), xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax)
{
}

void Vec2FloatAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->xmin = json["xmin"];
  this->xmax = json["xmax"];
  this->ymin = json["ymin"];
  this->ymax = json["ymax"];
}

nlohmann::json Vec2FloatAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["xmin"] = this->xmin;
  json["xmax"] = this->xmax;
  json["ymin"] = this->ymin;
  json["ymax"] = this->ymax;
  return json;
}

std::string Vec2FloatAttribute::to_string()
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
