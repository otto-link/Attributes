/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file string_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a string attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the StringAttribute class, which represents
 * an attribute that stores a string value. The class provides functions for
 * setting and getting the string value, JSON serialization/deserialization,
 * and label handling for true and false states.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class StringAttribute
 * @brief A class representing a string attribute.
 *
 * StringAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent string values. It provides methods to access and modify the string
 * value, serialize and deserialize to/from JSON, and handle different labels
 * for true and false states.
 */
class StringAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a StringAttribute with a string value and label.
   *
   * @param label The label describing the attribute.
   * @param value The string value to initialize the attribute with.
   */
  StringAttribute(const std::string &label, const std::string &value);

  /**
   * @brief Get the string value of the attribute.
   *
   * @return string The current value of the attribute.
   */
  std::string get_value() const { return this->value; }

  /**
   * @brief Set the string value of the attribute.
   *
   * @param new_value The new string value to set.
   */
  void set_value(const std::string &new_value) { this->value = new_value; }

  /**
   * @brief Convert the string value to a string...
   *
   * @return std::string The string representation of the string value.
   */
  std::string to_string() override { return this->value; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state from a provided JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * @return nlohmann::json A JSON object representing the attribute's current state.
   */
  nlohmann::json json_to() const override;

private:
  std::string value; /**< The string value of the attribute */
};

} // namespace attr
