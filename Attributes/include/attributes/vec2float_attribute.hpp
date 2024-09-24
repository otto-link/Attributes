/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec2float_attribute.hpp
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

class Vec2FloatAttribute : public AbstractAttribute
{
public:
  Vec2FloatAttribute() = delete;

  Vec2FloatAttribute(const std::string &label);

  Vec2FloatAttribute(std::vector<float> value,
                     float              xmin,
                     float              xmax,
                     float              ymin,
                     float              ymax,
                     const std::string &label = "");

  BoundCheck get_bound_check() const { return this->bound_check; }

  std::vector<float> get_value() const { return this->value; }

  float get_xmin() const { return this->xmin; }

  float get_xmax() const { return this->xmax; }

  float get_ymin() const { return this->ymin; }

  float get_ymax() const { return this->ymax; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string();

private:
  std::vector<float> value;
  float              xmin, xmax;
  float              ymin, ymax;
};

} // namespace attr
