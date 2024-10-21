/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file filename_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines attribute types, a base class for attributes, and utility functions for
 *        handling attributes in the application. Includes functionality for type-checking
 *        and JSON conversion of attribute data.
 *
 * This header provides the definition of different types of attributes (e.g., Bool,
 * Color, Filename) and their corresponding string representation. It includes an abstract
 * class for attribute objects, handling functionality like label setting, type retrieval,
 * and JSON serialization/deserialization.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include <iostream>
#include <string>

#include "attributes/logger.hpp"
#include "nlohmann/json.hpp"

namespace attr
{

/**
 * @enum AttributeType
 * @brief Enumeration of various attribute types.
 *
 * This enumeration defines different attribute types that can be used, such as
 * Bool, Color, Integer, Filename, Float, and others. It provides a mapping
 * between each type and its string representation for more human-readable outputs.
 */
enum AttributeType
{
  BOOL,  /**< Boolean attribute */
  COLOR, /**< Color attribute */
  COLOR_GRADIENT,
  INT,      /**< Integer attribute */
  FILENAME, /**< Filename attribute */
  FLOAT,    /**< Floating-point number attribute */
  HMAP_ARRAY,
  HMAP_CLOUD,
  HMAP_PATH,
  MAP_ENUM,  /**< Enum attribute */
  RANGE,     /**< Range attribute */
  SEED,      /**< Random seed attribute */
  VEC_FLOAT, /**< Vector of floats */
  VEC2FLOAT, /**< (x, y) floats */
  WAVE_NB,   /**< Wavenumber attribute */
  INVALID,   /**< Invalid attribute */
};

/**
 * @brief A mapping between AttributeType and its string representation.
 *
 * This map is used to provide string representations for attribute types,
 * making it easier to display attribute type information in logs or UIs.
 */
static std::map<AttributeType, std::string> attribute_type_map = {
    {AttributeType::BOOL, "Bool"},
    {AttributeType::COLOR, "Color"},
    {AttributeType::COLOR_GRADIENT, "Color gradient"},
    {AttributeType::INT, "Integer"},
    {AttributeType::FILENAME, "Filename"},
    {AttributeType::FLOAT, "Float"},
    {AttributeType::HMAP_ARRAY, "Array"},
    {AttributeType::HMAP_CLOUD, "Cloud"},
    {AttributeType::HMAP_PATH, "Path"},
    {AttributeType::MAP_ENUM, "Enumeration"},
    {AttributeType::RANGE, "Value range"},
    {AttributeType::SEED, "Random seed number"},
    {AttributeType::VEC_FLOAT, "Vector of floats"},
    {AttributeType::VEC2FLOAT, "Vec2Float"},
    {AttributeType::WAVE_NB, "Wavenumber"},
};

/**
 * @enum BoundCheck
 * @brief Enumeration for checking the bounds of an attribute.
 *
 * Specifies whether bound checking is enabled for the attribute, and if so,
 * whether it's applied to the upper bound, lower bound, or both.
 */
enum BoundCheck
{
  UNCHECKED,   /**< No bounds checking */
  UPPER_ONLY,  /**< Only upper bound checked */
  LOWER_ONLY,  /**< Only lower bound checked */
  UPPER_LOWER, /**< Both upper and lower bounds checked */
};

/**
 * @class AbstractAttribute
 * @brief A base class for defining attributes with labels, types, and bound checking.
 *
 * This class provides the foundation for all attribute types. It includes functionality
 * to set and get labels, retrieve the attribute type, and handle JSON serialization and
 * deserialization. It also provides a utility function to dynamically cast the attribute
 * to a specific type.
 */
class AbstractAttribute
{
public:
  /**
   * @brief Constructor for AbstractAttribute.
   *
   * Initializes an attribute with a specific type, label, and bound checking
   * configuration.
   *
   * @param type The type of the attribute.
   * @param label A label describing the attribute.
   * @param bound_check The bound check policy for this attribute.
   */
  AbstractAttribute(const AttributeType &type,
                    const std::string   &label,
                    const BoundCheck    &bound_check);

  /**
   * @brief Get the label of the attribute.
   *
   * @return std::string The label of the attribute.
   */
  std::string get_label() const { return this->label; }

  /**
   * @brief Get the type of the attribute.
   *
   * @return AttributeType The type of the attribute.
   */
  AttributeType get_type() const { return this->type; }

  /**
   * @brief Get a pointer to the current attribute, cast to the requested type.
   *
   * This function attempts to dynamically cast the attribute to the requested type.
   * If the cast fails, a critical error is logged, and an exception is thrown.
   *
   * @tparam T The expected type of the attribute.
   * @return T* A pointer to the attribute if the cast is successful.
   * @throws std::runtime_error If the cast fails.
   */
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

  /**
   * @brief Deserialize attribute data from JSON.
   *
   * This virtual function loads the attribute's state from the provided JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  virtual void json_from(nlohmann::json const &json);

  /**
   * @brief Serialize the attribute's data to JSON.
   *
   * This virtual function generates a JSON representation of the attribute's state.
   *
   * @return nlohmann::json The JSON object containing the serialized attribute data.
   */
  virtual nlohmann::json json_to() const;

  /**
   * @brief Set the label for the attribute.
   *
   * This function allows modifying the label associated with the attribute.
   *
   * @param new_label The new label to set.
   */
  void set_label(const std::string &new_label) { this->label = new_label; }

  /**
   * @brief Converts the current object to a string representation.
   *
   * This pure virtual function must be overridden by derived classes to provide
   * a string representation of the object. The content and format of the returned
   * string are defined by the implementation in the derived class.
   *
   * @return std::string A string representation of the object.
   */
  virtual std::string to_string() = 0;

protected:
  AttributeType type = AttributeType::INVALID; /**< The type of the attribute */
  std::string   label = "";                    /**< The label describing the attribute */
  BoundCheck    bound_check; /**< The bound check policy for this attribute */
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
