/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// IntAttribute
// =====================================

class IntAttribute : public AbstractAttribute
{
public:
  IntAttribute(const std::string &label,
               int                value,
               int                vmin = -INT_MAX,
               int                vmax = INT_MAX,
               std::string        value_format = "{}");

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  int         get_value() const;
  std::string get_value_format() const;
  int         get_vmin() const;
  int         get_vmax() const;
  void        set_value(const int &new_value);
  std::string to_string() override;

private:
  int         value;
  int         vmin;
  int         vmax;
  std::string value_format;
};

} // namespace attr
