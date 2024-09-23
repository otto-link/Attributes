#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class SeedAttribute : public AbstractAttribute
{
public:
  SeedAttribute() = delete;

  SeedAttribute(uint value = 0, const std::string &label = "")
      : AbstractAttribute(AttributeType::SEED, label, BoundCheck::UNCHECKED), value(value)
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
    std::cout << json.dump(4) << "\n";
    return json;
  }

  void set_value(const uint &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  uint value;
};

} // namespace attr
