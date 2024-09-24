/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file float_attribute.hpp
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

class FloatAttribute : public AbstractAttribute
{
public:
  FloatAttribute() = delete;

  FloatAttribute(float              value,
                 float              vmin,
                 float              vmax,
                 const std::string &label,
                 const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER);

  BoundCheck get_bound_check() const { return this->bound_check; }

  float get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const float &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  float value;
  float vmin;
  float vmax;
};

} // namespace attr
