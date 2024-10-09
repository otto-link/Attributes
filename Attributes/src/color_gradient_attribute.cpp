/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/color_gradient_attribute.hpp"
#include "attributes/widgets/color_widget.hpp"

namespace attr
{

ColorGradientAttribute::ColorGradientAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::COLOR_GRADIENT, label, BoundCheck::UNCHECKED)
{
}

ColorGradientAttribute::ColorGradientAttribute(std::vector<std::vector<float>> value,
                                               const std::string              &label)
    : AbstractAttribute(AttributeType::COLOR_GRADIENT, label, BoundCheck::UNCHECKED),
      value(value)
{
}

void ColorGradientAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<std::vector<float>>>();
}

nlohmann::json ColorGradientAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  return json;
}

std::string ColorGradientAttribute::to_string()
{
  std::string str = "";
  for (auto &vec : this->value)
  {
    str += "(";
    for (auto &v : vec)
      str += std::to_string(v) + ", ";
    str += ")\n";
  }
  return str;
}

} // namespace attr
