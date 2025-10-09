/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// VecFloatAttribute
// =====================================

class VecFloatAttribute : public AbstractAttribute
{
public:
  VecFloatAttribute(const std::string        &label,
                    const std::vector<float> &value,
                    const float               vmin,
                    const float               vmax);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<float>  get_value() const;
  std::vector<float> *get_value_ref();
  float               get_vmin() const;
  float               get_vmax() const;
  void                set_value(const std::vector<float> &new_value);
  std::string         to_string() override;

private:
  std::vector<float> value;
  float              vmin;
  float              vmax;
};

} // namespace attr
