/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file seed_attribute.hpp
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

class SeedAttribute : public AbstractAttribute
{
public:
  SeedAttribute();

  SeedAttribute(uint value, const std::string &label);

  uint get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const uint &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  uint value;
};

} // namespace attr
