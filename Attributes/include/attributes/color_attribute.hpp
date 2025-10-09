/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// ColorAttribute
// =====================================

class ColorAttribute : public AbstractAttribute
{
public:
  ColorAttribute(const std::string &label, const std::vector<float> &value);
  ColorAttribute(const std::string &label, float r, float g, float b, float a);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<float> get_value() const;
  void               set_value(const std::vector<float> &new_value);
  std::string        to_string();

private:
  std::vector<float> value = {1.f, 1.f, 1.f, 1.f};
};

} // namespace attr