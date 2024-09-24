/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/int_attribute.hpp"
#include "attributes/widgets/int_widget.hpp"

namespace attr
{

IntAttribute::IntAttribute(int                value,
                           int                vmin,
                           int                vmax,
                           const std::string &label,
                           const BoundCheck  &bound_check)
    : AbstractAttribute(AttributeType::INT, label, bound_check), value(value), vmin(vmin),
      vmax(vmax)
{
}

void IntAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
}

nlohmann::json IntAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  return json;
}

} // namespace attr
