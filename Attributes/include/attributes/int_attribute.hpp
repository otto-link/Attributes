/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file int_attribute.hpp
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

class IntAttribute : public AbstractAttribute
{
public:
  IntAttribute() = delete;

  IntAttribute(int                value,
               int                vmin,
               int                vmax,
               const std::string &label,
               const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER);

  BoundCheck get_bound_check() const { return this->bound_check; }

  int get_value() const { return this->value; }

  int get_vmin() const { return this->vmin; }

  int get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const int &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  int value;
  int vmin;
  int vmax;
};

} // namespace attr
