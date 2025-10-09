/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/vec2float_attribute.hpp"

namespace attr
{

Vec2FloatAttribute::Vec2FloatAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::VEC2FLOAT, label), value({0.5f, 0.5f}), xmin(0.f),
      xmax(1.f), ymin(0.f), ymax(1.f)
{
  this->save_state();
  this->save_initial_state();
}

Vec2FloatAttribute::Vec2FloatAttribute(const std::string        &label,
                                       const std::vector<float> &value,
                                       const float               xmin,
                                       const float               xmax,
                                       const float               ymin,
                                       const float               ymax)
    : AbstractAttribute(AttributeType::VEC2FLOAT, label), value(value), xmin(xmin),
      xmax(xmax), ymin(ymin), ymax(ymax)
{
  this->save_state();
  this->save_initial_state();
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

std::vector<float> Vec2FloatAttribute::get_value() const { return this->value; }

float Vec2FloatAttribute::get_xmin() const { return this->xmin; }

float Vec2FloatAttribute::get_xmax() const { return this->xmax; }

float Vec2FloatAttribute::get_ymin() const { return this->ymin; }

float Vec2FloatAttribute::get_ymax() const { return this->ymax; }

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

void Vec2FloatAttribute::set_value(const std::vector<float> &new_value)
{
  this->value = new_value;
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
