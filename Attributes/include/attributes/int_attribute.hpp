/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file int_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines an integer attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the IntAttribute class, which represents
 * an attribute that stores an integer value with optional minimum and maximum bounds.
 * The class provides functions for setting and getting the integer value, as well as
 * JSON serialization/deserialization, and string conversion of the value.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class IntAttribute
 * @brief A class representing an integer attribute with bounds.
 *
 * IntAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent integer values with optional bounds (minimum and maximum).
 * It provides methods to access and modify the value, handle bounds checking,
 * serialize and deserialize to/from JSON, and convert the value to a string.
 */
class IntAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize an IntAttribute with a value, bounds, and label.
   *
   * @param value The integer value associated with the attribute.
   * @param vmin The minimum bound for the value.
   * @param vmax The maximum bound for the value.
   * @param label A label describing the attribute.
   * @param bound_check Specifies whether bounds checking is enabled (optional, defaults
   * to UPPER_LOWER).
   */
  IntAttribute(const std::string &label,
               int                value,
               int                vmin = -INT_MAX,
               int                vmax = INT_MAX,
               std::string        value_format = "{}");

  /**
   * @brief Get the integer value of the attribute.
   *
   * Returns the current integer value stored in the attribute.
   *
   * @return int The current integer value.
   */
  int get_value() const { return this->value; }

  std::string get_value_format() const { return this->value_format; }

  /**
   * @brief Get the minimum bound of the attribute.
   *
   * Returns the minimum bound for the integer value, if bounds checking is enabled.
   *
   * @return int The minimum bound.
   */
  int get_vmin() const { return this->vmin; }

  /**
   * @brief Get the maximum bound of the attribute.
   *
   * Returns the maximum bound for the integer value, if bounds checking is enabled.
   *
   * @return int The maximum bound.
   */
  int get_vmax() const { return this->vmax; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including its value and bounds, from a provided JSON
   * object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including its value
   * and bounds.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Set the integer value of the attribute.
   *
   * Updates the attribute with a new integer value.
   *
   * @param new_value The new integer value to set.
   */
  void set_value(const int &new_value) { this->value = new_value; }

  /**
   * @brief Convert the integer value to a string representation.
   *
   * Returns the integer value as a string.
   *
   * @return std::string The string representation of the integer value.
   */
  std::string to_string() { return std::to_string(this->value); }

private:
  int         value; /**< The integer value of the attribute */
  int         vmin;  /**< The minimum bound for the integer value */
  int         vmax;  /**< The maximum bound for the integer value */
  std::string value_format;
};

} // namespace attr
