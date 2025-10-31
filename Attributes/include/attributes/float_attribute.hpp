/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// FloatAttribute
// =====================================

class FloatAttribute : public AbstractAttribute
{
public:
  FloatAttribute(const std::string &label,
                 float              value,
                 float              vmin = -FLT_MAX,
                 float              vmax = FLT_MAX,
                 std::string        value_format = "{:.3f}",
                 bool               log_scale = false);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  bool        get_log_scale() const;
  float       get_value() const;
  std::string get_value_format() const;
  float       get_vmin() const;
  float       get_vmax() const;
  void        set_value(const float &new_value);
  std::string to_string() override;

private:
  float       value;
  float       vmin;
  float       vmax;
  std::string value_format;
  bool        log_scale;
};

} // namespace attr
