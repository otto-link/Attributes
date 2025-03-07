/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/seed_attribute.hpp"

namespace attr
{

SeedAttribute::SeedAttribute() : AbstractAttribute(AttributeType::SEED, "Seed"), value(0)
{
}

SeedAttribute::SeedAttribute(uint value, const std::string &label)
    : AbstractAttribute(AttributeType::SEED, label), value(value)
{
}

void SeedAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<uint>();
}

nlohmann::json SeedAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  return json;
}

} // namespace attr
