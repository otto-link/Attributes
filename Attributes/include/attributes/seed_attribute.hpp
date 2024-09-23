#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class SeedAttribute : public AbstractAttribute
{
public:
  SeedAttribute()
          : AbstractAttribute(AttributeType::SEED, "Seed", BoundCheck::LOWER_ONLY), value(0)
  {
  }

  SeedAttribute(uint value, const std::string &label)
      : AbstractAttribute(AttributeType::SEED, label, BoundCheck::LOWER_ONLY), value(value)
  {
  }

  uint get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"].get<uint>();
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    return json;
  }

  void set_value(const uint &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  uint value;
};

} // namespace attr
