/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file bool_attribute.hpp
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

class BoolAttribute : public AbstractAttribute
{
public:
  BoolAttribute() = delete;

  BoolAttribute(bool value);

  BoolAttribute(bool value, const std::string &label);

  BoolAttribute(bool value, const std::string &label, const std::string &label_checked);

  std::string get_label_checked() const { return this->label_checked; }

  bool get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const bool &new_value) { this->value = new_value; }

  std::string to_string() { return this->value ? "true" : "false"; }

private:
  bool        value;
  std::string label_checked;
};

} // namespace attr
