/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/bool_attribute.hpp"

namespace attr
{

BoolAttribute::BoolAttribute(const std::string &label, bool value)
    : AbstractAttribute(AttributeType::BOOL, label), value(value), label_true(""),
      label_false("")
{
  this->save_state();
  this->save_initial_state();
}

BoolAttribute::BoolAttribute(const std::string &label,
                             const std::string &label_true,
                             const std::string &label_false,
                             const bool         value)
    : AbstractAttribute(AttributeType::BOOL, label), value(value), label_true(label_true),
      label_false(label_false)
{
  this->save_state();
  this->save_initial_state();
}

std::string BoolAttribute::get_label_false() const { return this->label_false; }
std::string BoolAttribute::get_label_true() const { return this->label_true; }
bool        BoolAttribute::get_value() const { return this->value; }

void BoolAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get(json, "value", value);
  json_safe_get(json, "label_true", label_true);
  json_safe_get(json, "label_false", label_false);
}

nlohmann::json BoolAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["label_true"] = this->label_true;
  json["label_false"] = this->label_false;
  return json;
}

void BoolAttribute::set_value(const bool &new_value) { this->value = new_value; }

std::string BoolAttribute::to_string() { return this->value ? "true" : "false"; }

} // namespace attr
