/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file range_attribute.hpp
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

class RangeAttribute : public AbstractAttribute
{
public:
  RangeAttribute();

  RangeAttribute(const std::string &label);

  RangeAttribute(std::vector<float> value,
                 float              vmin,
                 float              vmax,
                 const std::string &label = "",
                 bool               is_active = true,
                 const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER);

  BoundCheck get_bound_check() const { return this->bound_check; }

  bool get_is_active() const { return this->is_active; }

  std::vector<float> get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_is_active(bool new_state) { this->is_active = new_state; }

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string();

private:
  std::vector<float> value;
  float              vmin;
  float              vmax;
  bool               is_active;
};

} // namespace attr
