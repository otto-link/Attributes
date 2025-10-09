/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// WaveNbAttribute
// =====================================

class WaveNbAttribute : public AbstractAttribute
{
public:
  WaveNbAttribute();
  WaveNbAttribute(const std::string &label);
  WaveNbAttribute(const std::string        &label,
                  const std::vector<float> &value,
                  const float               vmin,
                  const float               vmax,
                  const bool                link_xy = true,
                  std::string               value_format = "{:.2f}");

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  bool               get_link_xy() const;
  std::vector<float> get_value() const;
  std::string        get_value_format() const;
  float              get_vmin() const;
  float              get_vmax() const;
  void               set_link_xy(const bool new_state);
  void               set_value(const std::vector<float> &new_value);
  std::string        to_string() override;

private:
  std::vector<float> value;
  float              vmin;
  float              vmax;
  bool               link_xy;
  std::string        value_format;
};

} // namespace attr
