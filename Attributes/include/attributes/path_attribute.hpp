/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file path_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "highmap/geometry/path.hpp"

#include "attributes/abstract_attribute.hpp"

namespace attr
{

class PathAttribute : public AbstractAttribute
{
public:
  PathAttribute(const std::string &label);

  PathAttribute(const std::string &label, const hmap::Path &value);

  hmap::Path get_value() const { return this->value; }

  hmap::Path *get_value_ref() { return &this->value; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const hmap::Path &new_value) { this->value = new_value; }

  std::string to_string();

private:
  hmap::Path value;
};

} // namespace attr
