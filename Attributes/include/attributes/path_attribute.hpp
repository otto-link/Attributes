/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "highmap/geometry/path.hpp"

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// PathAttribute
// =====================================

class PathAttribute : public AbstractAttribute
{
public:
  PathAttribute(const std::string &label);
  PathAttribute(const std::string &label, const hmap::Path &value);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  hmap::Path  get_value() const;
  hmap::Path *get_value_ref();
  void        set_value(const hmap::Path &new_value);
  std::string to_string() override;

private:
  hmap::Path value;
};

} // namespace attr
