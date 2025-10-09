/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// BoolAttribute
// =====================================

class BoolAttribute : public AbstractAttribute
{
public:
  BoolAttribute(const std::string &label, const bool value);
  BoolAttribute(const std::string &label,
                const std::string &label_true,
                const std::string &label_false,
                const bool         value);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::string get_label_false() const;
  std::string get_label_true() const;
  bool        get_value() const;
  void        set_value(const bool &new_value);
  std::string to_string() override;

private:
  bool        value;
  std::string label_true;
  std::string label_false;
};

} // namespace attr