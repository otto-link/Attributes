/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file float_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a float attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the FloatAttribute class, which represents
 * an attribute that stores a floating-point value with optional minimum and maximum
 * bounds. The class provides functions for setting and getting the float value, as well
 * as JSON serialization/deserialization, and string conversion of the value.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class FloatAttribute
 * @brief A class representing a floating-point attribute with bounds.
 *
 * FloatAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent floating-point values with optional bounds (minimum and maximum).
 * It provides methods to access and modify the value, handle bounds checking,
 * serialize and deserialize to/from JSON, and convert the value to a string.
 */
class FloatAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a FloatAttribute with a value, bounds, and label.
   *
   * @param value The floating-point value associated with the attribute.
   * @param vmin The minimum bound for the value.
   * @param vmax The maximum bound for the value.
   * @param label A label describing the attribute.
   * @param bound_check Specifies whether bounds checking is enabled (optional, defaults
   * to UPPER_LOWER).
   */
  FloatAttribute(const std::string &label,
                 float              value,
                 float              vmin = -FLT_MAX,
                 float              vmax = FLT_MAX,
                 std::string        value_format = "{:.3f}");

  /**
   * @brief Get the floating-point value of the attribute.
   *
   * Returns the current floating-point value stored in the attribute.
   *
   * @return float The current float value.
   */
  float get_value() const { return this->value; }

  std::string get_value_format() const { return this->value_format; }

  /**
   * @brief Get the minimum bound of the attribute.
   *
   * Returns the minimum bound for the float value, if bounds checking is enabled.
   *
   * @return float The minimum bound.
   */
  float get_vmin() const { return this->vmin; }

  /**
   * @brief Get the maximum bound of the attribute.
   *
   * Returns the maximum bound for the float value, if bounds checking is enabled.
   *
   * @return float The maximum bound.
   */
  float get_vmax() const { return this->vmax; }

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
   * @brief Set the floating-point value of the attribute.
   *
   * Updates the attribute with a new floating-point value.
   *
   * @param new_value The new float value to set.
   */
  void set_value(const float &new_value) { this->value = new_value; }

  /**
   * @brief Convert the float value to a string representation.
   *
   * Returns the float value as a string.
   *
   * @return std::string The string representation of the float value.
   */
  std::string to_string() { return std::to_string(this->value); }

private:
  float       value; /**< The floating-point value of the attribute */
  float       vmin;  /**< The minimum bound for the float value */
  float       vmax;  /**< The maximum bound for the float value */
  std::string value_format;
};

} // namespace attr
