/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/color_attribute.hpp"
#include "attributes/widgets/color_widget.hpp"

namespace attr
{

ColorAttribute::ColorAttribute(std::vector<float> value, const std::string &label)
    : AbstractAttribute(AttributeType::COLOR, label, BoundCheck::UNCHECKED), value(value)
{
}

ColorAttribute::ColorAttribute(float              r,
                               float              g,
                               float              b,
                               float              a,
                               const std::string &label)
    : AbstractAttribute(AttributeType::COLOR, label, BoundCheck::UNCHECKED),
      value({r, g, b, a})
{
}

void ColorAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
}

nlohmann::json ColorAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  return json;
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
