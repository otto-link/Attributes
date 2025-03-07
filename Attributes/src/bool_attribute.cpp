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
}

BoolAttribute::BoolAttribute(const std::string &label,
                             const std::string &label_true,
                             const std::string &label_false,
                             const bool         value)
    : AbstractAttribute(AttributeType::BOOL, label), value(value), label_true(label_true),
      label_false(label_false)
{
  this->save_state();
}

void BoolAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->label_true = json["label_true"];
  this->label_false = json["label_false"];
}

nlohmann::json BoolAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["label_true"] = this->label_true;
  json["label_false"] = this->label_false;
  return json;
}

} // namespace attr
