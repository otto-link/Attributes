/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/array_attribute.hpp"

namespace attr
{

ArrayAttribute::ArrayAttribute(const std::string &label, const glm::ivec2 &shape)
    : AbstractAttribute(AttributeType::ARRAY, label), shape(shape),
      vector(static_cast<size_t>(shape.x * shape.y), 0.f)
{
  this->save_state();
  this->save_initial_state();
}

ArrayAttribute::ArrayAttribute(const std::string        &label,
                               const glm::ivec2         &shape,
                               const std::vector<float> &vector)
    : AbstractAttribute(AttributeType::ARRAY, label), shape(shape), vector(vector)
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

  this->shape = glm::ivec2(json["shape.x"], json["shape.y"]);
  this->vector = json["vector"].get<std::vector<float>>();

  this->save_state();
  this->save_initial_state();
}

nlohmann::json ArrayAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  json["shape.x"] = this->shape.x;
  json["shape.y"] = this->shape.y;
  json["vector"] = this->vector;

  return json;
}

void ArrayAttribute::set_background_image_fct(std::function<QImage()> new_fct)
{
  this->background_image_fct = new_fct;
}

std::string ArrayAttribute::to_string()
{
  std::string str = "";

  if (!this->vector.empty())
  {
    str += "min: " + std::to_string(this->min()) + "; ";
    str += "max: " + std::to_string(this->max()) + "; ";
  }
  str += "shape: {" + std::to_string(this->shape.x) + ", " +
         std::to_string(this->shape.y) + "}";

  return str;
}

} // namespace attr
