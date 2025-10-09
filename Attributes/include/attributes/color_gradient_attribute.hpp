/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <array>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// Stop
// =====================================

struct Stop
{
  float                position;
  std::array<float, 4> color;
};

// =====================================
// Preset
// =====================================

struct Preset
{
  std::string       name;
  std::vector<Stop> stops;
};

// =====================================
// ColorGradientAttribute
// =====================================

class ColorGradientAttribute : public AbstractAttribute
{
public:
  ColorGradientAttribute(const std::string &label);
  ColorGradientAttribute(const std::string &label, const std::vector<Stop> &value);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<Preset> get_presets() const;
  std::vector<Stop>   get_value() const;
  std::vector<Stop>  *get_value_ref();
  void                set_presets(const std::vector<Preset> &new_presets);
  void                set_value(const std::vector<Stop> &new_value);
  std::string         to_string();

private:
  std::vector<Stop>   value = {{0.f, {0.f, 0.f, 0.f, 1.f}}, {1.f, {1.f, 1.f, 1.f, 1.f}}};
  std::vector<Preset> presets;
};

} // namespace attr
