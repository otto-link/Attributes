/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// StringAttribute
// =====================================

class StringAttribute : public AbstractAttribute
{
public:
  StringAttribute(const std::string &label, const std::string &value);
  StringAttribute(const std::string &label, const std::string &value, bool read_only);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  bool        get_read_only();
  std::string get_value() const;
  void        set_read_only(bool new_read_only);
  void        set_value(const std::string &new_value);
  std::string to_string() override;

private:
  std::string value;
  bool        read_only = false; // editable or not
};

} // namespace attr
