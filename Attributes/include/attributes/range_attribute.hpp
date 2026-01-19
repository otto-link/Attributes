/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <functional>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

using PairVec = std::pair<std::vector<float>, std::vector<float>>;

// =====================================
// RangeAttribute
// =====================================

class RangeAttribute : public AbstractAttribute
{
public:
  RangeAttribute();
  RangeAttribute(const std::string &label, const bool is_active = true);
  RangeAttribute(const std::string &label,
                 const glm::vec2   &value,
                 const float        vmin,
                 const float        vmax,
                 const bool         is_active = true,
                 std::string        value_format = "{:.2f}");

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  bool                     get_autorange() const;
  std::function<PairVec()> get_histogram_fct() const;
  bool                     get_is_active() const;
  glm::vec2                get_value() const;
  std::string              get_value_format() const;
  float                    get_vmin() const;
  float                    get_vmax() const;
  void                     set_autorange(bool new_state);
  void                     set_histogram_fct(std::function<PairVec()> new_histogram_fct);
  void                     set_is_active(bool new_state);
  void                     set_value(const glm::vec2 &new_value);
  std::string              to_string() override;

private:
  glm::vec2                value;
  float                    vmin;
  float                    vmax;
  bool                     is_active;
  std::string              value_format;
  std::function<PairVec()> histogram_fct = nullptr;
  bool                     autorange = false;
};

} // namespace attr
