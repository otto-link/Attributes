/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <cfloat>  // FLT_MAX
#include <climits> // INT_MAX
#include <iostream>
#include <string>

#include "attributes/logger.hpp"
#include "nlohmann/json.hpp"

namespace attr
{

enum AttributeType
{
  BOOL,   /**< Boolean attribute */
  CHOICE, /**< Choice attribute */
  COLOR,  /**< Color attribute */
  COLOR_GRADIENT,
  ENUM,     /**< Enum attribute */
  FILENAME, /**< Filename attribute */
  FLOAT,    /**< Floating-point number attribute */
  HMAP_ARRAY,
  HMAP_CLOUD,
  HMAP_PATH,
  INT,       /**< Integer attribute */
  RANGE,     /**< Range attribute */
  SEED,      /**< Random seed attribute */
  STRING,    /**< String attribute */
  VEC_FLOAT, /**< Vector of floats */
  VEC_INT,   /**< Vector of integers */
  VEC2FLOAT, /**< (x, y) floats */
  WAVE_NB,   /**< Wavenumber attribute */
  INVALID,   /**< Invalid attribute */
};

// A mapping between AttributeType and its string representation.
static std::map<AttributeType, std::string> attribute_type_map = {
    {AttributeType::BOOL, "Bool"},
    {AttributeType::CHOICE, "Choice"},
    {AttributeType::COLOR, "Color"},
    {AttributeType::COLOR_GRADIENT, "Color gradient"},
    {AttributeType::ENUM, "Enumeration"},
    {AttributeType::FILENAME, "Filename"},
    {AttributeType::FLOAT, "Float"},
    {AttributeType::HMAP_ARRAY, "Array"},
    {AttributeType::HMAP_CLOUD, "Cloud"},
    {AttributeType::HMAP_PATH, "Path"},
    {AttributeType::INT, "Integer"},
    {AttributeType::RANGE, "Value range"},
    {AttributeType::SEED, "Random seed number"},
    {AttributeType::STRING, "String"},
    {AttributeType::VEC_FLOAT, "Vector of floats"},
    {AttributeType::VEC_INT, "Vector of integers"},
    {AttributeType::VEC2FLOAT, "Vec2Float"},
    {AttributeType::WAVE_NB, "Wavenumber"},
};

// =====================================
// AbstractAttribute
// =====================================

class AbstractAttribute
{
public:
  AbstractAttribute(const AttributeType &type, const std::string &label);
  virtual ~AbstractAttribute() = default;

  virtual void           json_from(nlohmann::json const &json);
  virtual nlohmann::json json_to() const;

  std::string         get_label() const;
  std::string         get_description() const;
  AttributeType       get_type() const;
  std::string         get_type_string() const;
  void                set_label(const std::string &new_label);
  void                set_description(const std::string &new_description);
  virtual std::string to_string() = 0;

  // Get a pointer to the current attribute, cast to the requested type.
  template <class T = void> T *get_ref()
  {
    T *ptr = dynamic_cast<T *>(this);
    if (ptr)
      return ptr;
    else
    {
      Logger::log()->critical(
          "in Attribute, trying to get an attribute type which is not "
          "compatible with the current instance. Get type is: [{}]",
          typeid(T).name());
      throw std::runtime_error("wrong type");
    }
  }

  void reset_to_initial_state();
  void reset_to_save_state();
  void save_initial_state();
  void save_state();

protected:
  AttributeType  type = AttributeType::INVALID;
  std::string    label = "";
  std::string    description = "";
  nlohmann::json attribute_state;
  nlohmann::json attribute_initial_state;
};

// Helper - Creates a unique pointer to an attribute of the specified type.
template <typename AttributeType, typename... Args>
std::unique_ptr<AttributeType> create_attr(Args &&...args)
{
  return std::make_unique<AttributeType>(std::forward<Args>(args)...);
}

} // namespace attr
