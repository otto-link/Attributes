/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// Vec2FloatAttribute
// =====================================

class Vec2FloatAttribute : public AbstractAttribute
{
public:
  Vec2FloatAttribute() = delete;
  Vec2FloatAttribute(const std::string &label);
  Vec2FloatAttribute(const std::string        &label,
                     const std::vector<float> &value,
                     const float               xmin,
                     const float               xmax,
                     const float               ymin,
                     const float               ymax);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<float> get_value() const;
  float              get_xmin() const;
  float              get_xmax() const;
  float              get_ymin() const;
  float              get_ymax() const;
  void               set_value(const std::vector<float> &new_value);
  std::string        to_string() override;

private:
  std::vector<float> value;
  float              xmin, xmax;
  float              ymin, ymax;
};

} // namespace attr
