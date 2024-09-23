#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class MapEnumAttribute : public AbstractAttribute
{
public:
  MapEnumAttribute() = delete;

  MapEnumAttribute(std::string                value,
                   std::map<std::string, int> map,
                   const std::string         &label = "")
      : AbstractAttribute(AttributeType::INT, label, BoundCheck::UNCHECKED), value(value),
        map(map)
  {
  }

  std::string get_value() const { return this->value; }

  std::map<std::string, int> get_map() const { return this->map; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    std::cout << json.dump(4) << "\n";
    return json;
  }

  void set_value(const std::string &new_value) { this->value = new_value; }

  std::string to_string() { return this->value; }

private:
  std::string                value;
  std::map<std::string, int> map;
};

} // namespace attr
