/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <array>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// ColorAttribute
// =====================================

class ColorAttribute : public AbstractAttribute
{
public:
  ColorAttribute(const std::string &label, const std::array<float, 4> &value);
  ColorAttribute(const std::string &label, float r, float g, float b, float a);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::array<float, 4> get_value() const;
  void                 set_value(const std::array<float, 4> &new_value);
  std::string          to_string();

private:
  std::array<float, 4> value = {1.f, 1.f, 1.f, 1.f};
};

} // namespace attr