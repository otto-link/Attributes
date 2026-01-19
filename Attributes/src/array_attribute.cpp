/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/array_attribute.hpp"

namespace attr
{

ArrayAttribute::ArrayAttribute(const std::string &label, const glm::ivec2 &shape)
    : AbstractAttribute(AttributeType::HMAP_ARRAY, label)
{
  this->value = hmap::Array(shape);

  this->save_state();
  this->save_initial_state();
}

ArrayAttribute::ArrayAttribute(const std::string &label, const hmap::Array &value)
    : AbstractAttribute(AttributeType::HMAP_ARRAY, label), value(value)
{
  this->save_state();
  this->save_initial_state();
}

std::function<QImage()> ArrayAttribute::get_background_image_fct() const
{
  return this->background_image_fct;
}

void ArrayAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);

  glm::ivec2 shape(json["shape.x"], json["shape.y"]);
  this->value = hmap::Array(shape);

  std::vector<float> vector = json["vector"].get<std::vector<float>>();
  this->value.vector = vector;

  this->save_state();
  this->save_initial_state();
}

nlohmann::json ArrayAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  json["shape.x"] = this->value.shape.x;
  json["shape.y"] = this->value.shape.y;
  json["vector"] = this->value.vector;

  return json;
}

void ArrayAttribute::set_background_image_fct(std::function<QImage()> new_fct)
{
  this->background_image_fct = new_fct;
}

std::string ArrayAttribute::to_string()
{
  std::string str = "";
  str += "min: " + std::to_string(this->value.min()) + "; ";
  str += "max: " + std::to_string(this->value.max()) + "; ";
  str += "shape: {" + std::to_string(this->value.shape.x) + ", " +
         std::to_string(this->value.shape.y) + "}";

  return str;
}

} // namespace attr
