/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/cloud_attribute.hpp"

namespace attr
{

CloudAttribute::CloudAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::CLOUD, label)
{
  this->value = std::vector<glm::vec3>();
  this->save_state();
  this->save_initial_state();
}

CloudAttribute::CloudAttribute(const std::string &label, bool are_points_connected)
    : AbstractAttribute(AttributeType::CLOUD, label),
      are_points_connected(are_points_connected)
{
  this->value = std::vector<glm::vec3>();
  this->save_state();
  this->save_initial_state();
}

CloudAttribute::CloudAttribute(const std::string            &label,
                               const std::vector<glm::vec3> &value)
    : AbstractAttribute(AttributeType::CLOUD, label), value(value)
{
  this->save_state();
  this->save_initial_state();
}

bool CloudAttribute::get_are_points_connected() const
{
  return this->are_points_connected;
}

std::function<QImage()> CloudAttribute::get_background_image_fct() const
{
  return this->background_image_fct;
}

void CloudAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);

  std::vector<float> x = json["x"].get<std::vector<float>>();
  std::vector<float> y = json["y"].get<std::vector<float>>();
  std::vector<float> v = json["values"].get<std::vector<float>>();

  this->value.clear();
  this->value.reserve(x.size());

  for (size_t k = 0; k < x.size(); ++k)
    this->value.push_back({x[k], y[k], v[k]});
}

nlohmann::json CloudAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  std::vector<float> x, y, v;
  x.reserve(this->value.size());
  y.reserve(this->value.size());
  v.reserve(this->value.size());

  for (const auto &p : this->value)
  {
    x.push_back(p.x);
    y.push_back(p.y);
    v.push_back(p.z);
  }

  json["x"] = x;
  json["y"] = y;
  json["values"] = v;

  return json;
}

void CloudAttribute::set_are_points_connected(const bool new_state)
{
  this->are_points_connected = new_state;
}

void CloudAttribute::set_background_image_fct(std::function<QImage()> new_fct)
{
  this->background_image_fct = new_fct;
}

void CloudAttribute::set_value(const std::vector<glm::vec3> &new_value)
{
  this->value = new_value;
}

std::string CloudAttribute::to_string()
{
  std::string str = "";

  str += "npoints: " + std::to_string(this->value.size());
  for (const auto &p : this->value)
    str += "\n(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " +
           std::to_string(p.z) + ")";

  return str;
}

} // namespace attr
