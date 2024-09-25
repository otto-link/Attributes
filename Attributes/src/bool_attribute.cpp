/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/bool_attribute.hpp"
#include "attributes/widgets/bool_widget.hpp"

namespace attr
{

BoolAttribute::BoolAttribute(bool value)
    : AbstractAttribute(AttributeType::BOOL, "", BoundCheck::UNCHECKED), value(value),
      label_checked("")
{
}

BoolAttribute::BoolAttribute(bool value, const std::string &label)
    : AbstractAttribute(AttributeType::BOOL, label, BoundCheck::UNCHECKED), value(value),
      label_checked(label)
{
}

BoolAttribute::BoolAttribute(bool               value,
                             const std::string &label,
                             const std::string &label_checked)
    : AbstractAttribute(AttributeType::BOOL, label, BoundCheck::UNCHECKED), value(value),
      label_checked(label_checked)
{
}

void BoolAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->label_checked = json["label_checked"];
}

nlohmann::json BoolAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["label_checked"] = this->label_checked;
  return json;
}

} // namespace attr
