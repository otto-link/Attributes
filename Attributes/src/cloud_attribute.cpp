/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/cloud_attribute.hpp"

namespace attr
{

CloudAttribute::CloudAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::HMAP_CLOUD, label, BoundCheck::UNCHECKED)
{
  this->value = hmap::Cloud();
}

CloudAttribute::CloudAttribute(const hmap::Cloud &value, const std::string &label)
    : AbstractAttribute(AttributeType::HMAP_CLOUD, label, BoundCheck::UNCHECKED),
      value(value)
{
}

void CloudAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);

  std::vector<float> x = json["x"].get<std::vector<float>>();
  std::vector<float> y = json["y"].get<std::vector<float>>();
  std::vector<float> values = json["values"].get<std::vector<float>>();

  this->value = hmap::Cloud(x, y, values);
}

nlohmann::json CloudAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  json["x"] = this->value.get_x();
  json["y"] = this->value.get_y();
  json["values"] = this->value.get_values();

  return json;
}

std::string CloudAttribute::to_string()
{
  std::string str = "";

  str += "npoints: " + std::to_string(this->value.get_npoints());
  for (auto &p : this->value.points)
    str += "\n(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " +
           std::to_string(p.v) + ")";

  return str;
}

} // namespace attr
