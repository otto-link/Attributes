#pragma once
#include <string>

#include "nlohmann/json.hpp"

#include "attributes/logger.hpp"

#include <iostream>

namespace attr
{

enum AttributeType
{
  BOOL,
  COLOR,
  INT,
  FLOAT,
  MAP_ENUM,
  RANGE,
  SEED,
  VEC2FLOAT,
  WAVE_NB,
  INVALID,
};

static std::map<AttributeType, std::string> attribute_type_map = {
    {AttributeType::BOOL, "Bool"},
    {AttributeType::COLOR, "Color"},
    {AttributeType::INT, "Integer"},
    {AttributeType::FLOAT, "Float"},
    {AttributeType::MAP_ENUM, "Enumeration"},
    {AttributeType::RANGE, "Value range"},
    {AttributeType::SEED, "Random seed number"},
    {AttributeType::VEC2FLOAT, "Vec2Float"},
    {AttributeType::WAVE_NB, "Wavenumber"},
};

#define ATT_NO_BOUND_CHECK 1000000000

enum BoundCheck
{
  UNCHECKED,
  UPPER_ONLY,
  LOWER_ONLY,
  UPPER_LOWER,
};

class AbstractAttribute
{

public:
  AbstractAttribute() = delete;

  AbstractAttribute(const AttributeType &type,
                    const std::string   &label,
                    const BoundCheck    &bound_check)
      : type(type), label(label), bound_check(bound_check)
  {
  }

  std::string get_label() const { return this->label; }

  AttributeType get_type() const { return this->type; }

  template <class T = void> T *get_ref()
  {
    T *ptr = dynamic_cast<T *>(this);
    if (ptr)
      return ptr;
    else
    {
      QATLOG->critical("in Attribute, trying to get an attribute type which is not "
                       "compatible with the current instance. Get type is: [{}]",
                       typeid(T).name());
      throw std::runtime_error("wrong type");
    }
  }

  virtual void json_from(nlohmann::json const &json)
  {
    this->type = json["type"].get<AttributeType>();
    this->label = json["label"];
    this->bound_check = json["bound_check"].get<BoundCheck>();
  }

  virtual nlohmann::json json_to() const
  {
    nlohmann::json json;
    json["type"] = this->type;
    json["type_string"] = attribute_type_map.at(this->type);
    json["label"] = this->label;
    json["bound_check"] = this->bound_check;
    return json;
  }

  void set_label(const std::string &new_label) { this->label = new_label; }

protected:
  AttributeType type = AttributeType::INVALID;
  std::string   label = "";
  BoundCheck    bound_check;
};

} // namespace attr
