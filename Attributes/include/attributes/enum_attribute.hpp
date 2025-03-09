/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file map_enum_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a map enumeration attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the MapEnumAttribute class, which represents
 * an attribute that stores an enumeration using a map of string keys to integer values.
 * The class provides methods to access and modify the current choice, manage the
 * underlying map of possible choices, and perform JSON serialization/deserialization.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class MapEnumAttribute
 * @brief A class representing an attribute using a map for enumerations.
 *
 * MapEnumAttribute is derived from AbstractAttribute and is used to manage attributes
 * where a map of string keys to integer values represents an enumeration. The class
 * provides methods to get and set the current choice, modify the integer value associated
 * with a choice, serialize/deserialize to/from JSON, and convert the choice to a string.
 */
class EnumAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a MapEnumAttribute with a map of choices and a
   * label.
   *
   * @param map A map where keys are string labels, and values are integers representing
   * the enumeration.
   * @param label A label describing the attribute (optional).
   */
  EnumAttribute(const std::string &label, const std::map<std::string, int> &map);

  /**
   * @brief Constructor to initialize a MapEnumAttribute with a specific choice, map of
   * choices, and label.
   *
   * @param choice The initial choice for the attribute, represented as a string.
   * @param map A map where keys are string labels, and values are integers representing
   * the enumeration.
   * @param label A label describing the attribute (optional).
   */
  EnumAttribute(const std::string                &label,
                const std::map<std::string, int> &map,
                const std::string                &choice);

  /**
   * @brief Get the current choice of the attribute.
   *
   * Returns the current selected choice of the enumeration as a string.
   *
   * @return std::string The current choice.
   */
  std::string get_choice() const { return this->choice; }

  /**
   * @brief Get the integer value associated with the current choice.
   *
   * Returns the integer value corresponding to the current choice in the map.
   *
   * @return int The integer value of the current choice.
   */
  int get_value() const { return this->value; }

  /**
   * @brief Get the map of choices for the attribute.
   *
   * Returns the map of string keys and integer values that defines the possible choices
   * for the attribute.
   *
   * @return std::map<std::string, int> The map of possible choices.
   */
  std::map<std::string, int> get_map() const { return this->map; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including its current choice and map, from a provided
   * JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including its
   * choice and value.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Set the integer value associated with a specific choice.
   *
   * Updates the attribute with a new integer value corresponding to a new choice in the
   * map.
   *
   * @param new_value The new integer value to set.
   */
  void set_value(const int &new_value) { this->value = new_value; }

  /**
   * @brief Set the current choice for the attribute.
   *
   * Updates the attribute with a new choice from the map of possible choices.
   *
   * @param new_choice The new choice to set.
   */
  void set_choice(const std::string &new_choice) { this->choice = new_choice; }

  /**
   * @brief Convert the current choice to a string representation.
   *
   * Returns the current choice as a string.
   *
   * @return std::string The string representation of the current choice.
   */
  std::string to_string() { return this->choice; }

private:
  int         value;  /**< The integer value of the current choice */
  std::string choice; /**< The string key representing the current choice */
  std::map<std::string, int>
      map; /**< The map of possible choices (string key to integer value) */
};

} // namespace attr
