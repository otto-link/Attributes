/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file range_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a range attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the RangeAttribute class, which represents
 * an attribute that stores a range of float values with a minimum and maximum bound.
 * The class supports bound checking, active state management, and JSON serialization/
 * deserialization.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class RangeAttribute
 * @brief A class representing a range attribute with float values.
 *
 * The RangeAttribute class is derived from AbstractAttribute and is used to manage
 * attributes that store a range of float values, including a minimum and maximum bound.
 * The class provides methods for accessing the range, setting its value, controlling
 * the active state, and performing JSON serialization/deserialization.
 */
class RangeAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Default constructor.
   *
   * Initializes a RangeAttribute with default values for range and bounds.
   */
  RangeAttribute();

  /**
   * @brief Constructor to initialize a RangeAttribute with a label.
   *
   * @param label The label describing the attribute.
   * @param is_active Whether the attribute is active (optional, default is true).
   */
  RangeAttribute(const std::string &label, const bool is_active = true);

  /**
   * @brief Constructor to initialize a RangeAttribute with a value range, bounds, and
   * optional label.
   *
   * @param value A vector representing the range of values.
   * @param vmin The minimum bound for the range.
   * @param vmax The maximum bound for the range.
   * @param label The label describing the attribute (optional).
   * @param is_active Whether the attribute is active (optional, default is true).
   * @param bound_check The type of bound check to apply (optional, default is
   * BoundCheck::UPPER_LOWER).
   */
  RangeAttribute(const std::string        &label,
                 const std::vector<float> &value,
                 const float               vmin,
                 const float               vmax,
                 const bool                is_active = true);

  /**
   * @brief Get the active state of the attribute.
   *
   * @return bool True if the attribute is active, false otherwise.
   */
  bool get_is_active() const { return this->is_active; }

  /**
   * @brief Get the current range of values.
   *
   * @return std::vector<float> The current range of float values.
   */
  std::vector<float> get_value() const { return this->value; }

  /**
   * @brief Get the minimum bound for the range.
   *
   * @return float The minimum bound.
   */
  float get_vmin() const { return this->vmin; }

  /**
   * @brief Get the maximum bound for the range.
   *
   * @return float The maximum bound.
   */
  float get_vmax() const { return this->vmax; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including its value range, bounds, and active state from
   * a provided JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including its value
   * range, bounds, and active state.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Set the active state of the attribute.
   *
   * Updates whether the attribute is active or not.
   *
   * @param new_state The new active state (true or false).
   */
  void set_is_active(bool new_state) { this->is_active = new_state; }

  /**
   * @brief Set the value range of the attribute.
   *
   * Updates the attribute's range with new float values.
   *
   * @param new_value A vector representing the new range of values.
   */
  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  /**
   * @brief Convert the current range to a string representation.
   *
   * Returns the current range as a string.
   *
   * @return std::string The string representation of the current range.
   */
  std::string to_string();

private:
  std::vector<float> value;     /**< The current range of float values */
  float              vmin;      /**< The minimum bound for the range */
  float              vmax;      /**< The maximum bound for the range */
  bool               is_active; /**< The active state of the attribute */
};

} // namespace attr
