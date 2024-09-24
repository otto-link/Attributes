/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file wave_nb_attribute.hpp
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

class WaveNbAttribute : public AbstractAttribute
{
public:
  WaveNbAttribute();

  WaveNbAttribute(std::vector<float> value,
                  float              vmin,
                  float              vmax,
                  bool               link_xy = true,
                  const std::string &label = "",
                  const BoundCheck  &bound_check = BoundCheck::LOWER_ONLY);

  BoundCheck get_bound_check() const { return this->bound_check; }

  bool get_link_xy() const { return this->link_xy; }

  std::vector<float> get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_link_xy(const bool new_state) { this->link_xy = new_state; }

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string();

private:
  std::vector<float> value;
  float              vmin;
  float              vmax;
  bool               link_xy;
};

} // namespace attr
