/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/color_attribute.hpp"
#include "attributes/widgets/color_widget.hpp"

namespace attr
{

ColorAttribute::ColorAttribute(const std::string &label, const std::vector<float> &value)
    : AbstractAttribute(AttributeType::COLOR, label), value(value)
{
  this->save_state();
  this->save_initial_state();
}

ColorAttribute::ColorAttribute(const std::string &label,
                               float              r,
                               float              g,
                               float              b,
                               float              a)
    : AbstractAttribute(AttributeType::COLOR, label), value({r, g, b, a})
{
  this->save_state();
  this->save_initial_state();
}

std::vector<float> ColorAttribute::get_value() const { return this->value; }

void ColorAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get<std::vector<float>>(json, "value", value);
}

nlohmann::json ColorAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  return json;
}

void ColorAttribute::set_value(const std::vector<float> &new_value)
{
  this->value = new_value;
}

std::string ColorAttribute::to_string()
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
