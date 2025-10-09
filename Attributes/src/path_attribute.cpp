/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/path_attribute.hpp"

namespace attr
{

PathAttribute::PathAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::HMAP_PATH, label)
{
  this->value = hmap::Path();
  this->save_state();
  this->save_initial_state();
}

PathAttribute::PathAttribute(const std::string &label, const hmap::Path &value)
    : AbstractAttribute(AttributeType::HMAP_PATH, label), value(value)
{
  this->save_state();
  this->save_initial_state();
}

hmap::Path PathAttribute::get_value() const { return this->value; }

hmap::Path *PathAttribute::get_value_ref() { return &this->value; }

void PathAttribute::set_value(const hmap::Path &new_value) { this->value = new_value; }

void PathAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);

  std::vector<float> x = json["x"].get<std::vector<float>>();
  std::vector<float> y = json["y"].get<std::vector<float>>();
  std::vector<float> values = json["values"].get<std::vector<float>>();

  this->value = hmap::Path(x, y, values);
}

nlohmann::json PathAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  json["x"] = this->value.get_x();
  json["y"] = this->value.get_y();
  json["values"] = this->value.get_values();

  return json;
}

std::string PathAttribute::to_string()
{
  std::string str = "";

  str += "npoints: " + std::to_string(this->value.get_npoints());
  for (auto &p : this->value.points)
    str += "\n(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " +
           std::to_string(p.v) + ")";
  return str;
}

} // namespace attr
