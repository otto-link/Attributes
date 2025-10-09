/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

typedef unsigned int uint;

namespace attr
{

// =====================================
// SeedAttribute
// =====================================

class SeedAttribute : public AbstractAttribute
{
public:
  SeedAttribute();
  SeedAttribute(const std::string &label, const uint value = 0);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  uint        get_value() const;
  void        set_value(const uint &new_value);
  std::string to_string() override;

private:
  uint value;
};

} // namespace attr
