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
                    const BoundCheck    &bound_check);

  std::string get_label() const { return this->label; }

  AttributeType get_type() const { return this->type; }

  template <class T = void> T *get_ref()
  {
    T *ptr = dynamic_cast<T *>(this);
    if (ptr)
      return ptr;
    else
    {
      Logger::get_logger()->critical(
          "in Attribute, trying to get an attribute type which is not "
          "compatible with the current instance. Get type is: [{}]",
          typeid(T).name());
      throw std::runtime_error("wrong type");
    }
  }

  virtual void json_from(nlohmann::json const &json);

  virtual nlohmann::json json_to() const;

  void set_label(const std::string &new_label) { this->label = new_label; }

protected:
  AttributeType type = AttributeType::INVALID;
  std::string   label = "";
  BoundCheck    bound_check;
};

/**
 * @brief Creates a unique pointer to an attribute of the specified type.
 *
 * This function is a template that can create any type of attribute by forwarding
 * the provided arguments to the constructor of the attribute.
 *
 * @tparam AttributeType The type of the attribute to create. Must be a class that
 * inherits from an attribute base class.
 * @tparam Args Variadic template parameter that allows passing any number of arguments
 * to the constructor of the attribute.
 *
 * @param args The arguments to forward to the constructor of the attribute.
 * @return std::unique_ptr<AttributeType> A unique pointer to the newly created attribute.
 */
template <typename AttributeType, typename... Args>
std::unique_ptr<AttributeType> create_attr(Args &&...args)
{
  return std::make_unique<AttributeType>(std::forward<Args>(args)...);
}

} // namespace attr
