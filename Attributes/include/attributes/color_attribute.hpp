/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class ColorAttribute : public AbstractAttribute
{
public:
  ColorAttribute() = delete;

  ColorAttribute(std::vector<float> value, const std::string &label);

  ColorAttribute(float r, float g, float b, float a, const std::string &label);

  std::vector<float> get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string();

private:
  std::vector<float> value = {1.f, 1.f, 1.f, 1.f};
};

} // namespace attr
