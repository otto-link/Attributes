/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// VecIntAttribute
// =====================================

class VecIntAttribute : public AbstractAttribute
{
public:
  VecIntAttribute(const std::string      &label,
                  const std::vector<int> &value,
                  const int               vmin,
                  const int               vmax);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::vector<int>  get_value() const;
  std::vector<int> *get_value_ref();
  int               get_vmin() const;
  int               get_vmax() const;
  void              set_value(const std::vector<int> &new_value);
  std::string       to_string() override;

private:
  std::vector<int> value;
  int              vmin;
  int              vmax;
};

} // namespace attr
