#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class MapEnumAttribute : public AbstractAttribute
{
public:
  MapEnumAttribute() = delete;

  MapEnumAttribute(std::map<std::string, int> map, const std::string &label = "")
      : AbstractAttribute(AttributeType::MAP_ENUM, label, BoundCheck::UNCHECKED), map(map)
  {
    this->choice = map.begin()->first;
    this->value = map.begin()->second;
  }

  MapEnumAttribute(std::string                choice,
                   std::map<std::string, int> map,
                   const std::string         &label = "")
      : AbstractAttribute(AttributeType::MAP_ENUM, label, BoundCheck::UNCHECKED),
        choice(choice), map(map)
  {
    auto it = this->map.find(this->choice);

    if (it != this->map.end())
      this->value = it->second;
    else
    {
      this->choice = map.begin()->first;
      this->value = map.begin()->second;
      QATLOG->warn("Warning: input choice not found in the map, default value set to 0 "
                   "(choice: {}).",
                   this->choice);
    }
  }

  std::string get_choice() const { return this->choice; }

  int get_value() const { return this->value; }

  std::map<std::string, int> get_map() const { return this->map; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"];
    this->choice = json["choice"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["choice"] = this->choice;
    return json;
  }

  void set_value(const int &new_value) { this->value = new_value; }

  void set_choice(const std::string &new_choice) { this->choice = new_choice; }

  std::string to_string() { return this->choice; }

private:
  int                        value;
  std::string                choice;
  std::map<std::string, int> map;
};

} // namespace attr
