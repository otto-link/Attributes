/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <random>

#include "attributes/color_gradient_attribute.hpp"
#include "attributes/widgets/color_widget.hpp"

namespace attr
{

ColorGradientAttribute::ColorGradientAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::COLOR_GRADIENT, label)
{
  this->save_state();
  this->save_initial_state();
}

ColorGradientAttribute::ColorGradientAttribute(const std::string       &label,
                                               const std::vector<Stop> &value)
    : AbstractAttribute(AttributeType::COLOR_GRADIENT, label), value(value)
{
  this->save_state();
  this->save_initial_state();
}

std::vector<Preset> ColorGradientAttribute::get_presets() const { return this->presets; }

std::vector<Stop> ColorGradientAttribute::get_value() const { return this->value; }

std::vector<Stop> *ColorGradientAttribute::get_value_ref() { return &this->value; }

void ColorGradientAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);

  this->value.clear();

  if (json.contains("value"))
  {
    for (const auto &j : json["value"].items())
    {
      if (j.value().contains("position") && j.value().contains("color"))
      {
        Stop s{j.value()["position"], j.value()["color"]};
        this->value.push_back(s);
      }
    }
  }
}

nlohmann::json ColorGradientAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();

  for (auto &v : this->value)
  {
    json["value"].push_back({{"position", v.position}, {"color", v.color}});
  }

  return json;
}

void ColorGradientAttribute::set_presets(const std::vector<Preset> &new_presets)
{
  this->presets = new_presets;
}

void ColorGradientAttribute::set_value(const std::vector<Stop> &new_value)
{
  this->value = new_value;
}

void ColorGradientAttribute::shuffle_colors()
{
  // extract colors
  std::vector<std::array<float, 4>> colors;
  colors.reserve(this->value.size());
  for (const auto &s : this->value)
    colors.push_back(s.color);

  // shuffle colors
  std::random_device rd;
  std::mt19937       gen(rd());
  std::shuffle(colors.begin(), colors.end(), gen);

  // reassign shuffled colors back to value
  for (size_t i = 0; i < this->value.size(); ++i)
    this->value[i].color = colors[i];
}

std::string ColorGradientAttribute::to_string()
{
  std::string str = "";
  for (auto &v : this->value)
  {
    str += "(";
    str += std::to_string(v.position) + ", ";
    str += std::to_string(v.color[0]) + ", ";
    str += std::to_string(v.color[1]) + ", ";
    str += std::to_string(v.color[2]) + ", ";
    str += std::to_string(v.color[3]);
    str += ")\n";
  }
  return str;
}

} // namespace attr
