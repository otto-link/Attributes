/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "highmap/array.hpp"

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// ArrayAttribute
// =====================================

class ArrayAttribute : public AbstractAttribute
{
public:
  ArrayAttribute(const std::string &label, const hmap::Vec2<int> &shape);
  ArrayAttribute(const std::string &label, const hmap::Array &value);

  hmap::Vec2<int> get_shape() const { return this->value.shape; }
  hmap::Array     get_value() const { return this->value; }
  hmap::Array    *get_value_ref() { return &this->value; }
  void            set_value(const hmap::Array &new_value) { this->value = new_value; }
  std::string     to_string();

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

private:
  hmap::Array value;
};

} // namespace attr
