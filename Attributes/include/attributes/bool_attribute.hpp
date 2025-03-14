/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file bool_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a boolean attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the BoolAttribute class, which represents
 * an attribute that stores a boolean value. The class provides functions for
 * setting and getting the boolean value, JSON serialization/deserialization,
 * and label handling for true and false states.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class BoolAttribute
 * @brief A class representing a boolean attribute.
 *
 * BoolAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent boolean values. It provides methods to access and modify the boolean
 * value, serialize and deserialize to/from JSON, and handle different labels
 * for true and false states.
 */
class BoolAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a BoolAttribute with a boolean value and label.
   *
   * @param label The label describing the attribute.
   * @param value The boolean value to initialize the attribute with.
   */
  BoolAttribute(const std::string &label, const bool value);

  /**
   * @brief Constructor to initialize a BoolAttribute with a value, label, and labels
   * for true and false states.
   *
   * @param label The label describing the attribute.
   * @param label_true The label describing the true state of the attribute.
   * @param label_false The label describing the false state of the attribute.
   * @param value The boolean value to initialize the attribute with.
   */
  BoolAttribute(const std::string &label,
                const std::string &label_true,
                const std::string &label_false,
                const bool         value);

  /**
   * @brief Get the label describing the false state of the attribute.
   *
   * @return std::string The label for the false state.
   */
  std::string get_label_false() const { return this->label_false; }

  /**
   * @brief Get the label describing the true state of the attribute.
   *
   * @return std::string The label for the true state.
   */
  std::string get_label_true() const { return this->label_true; }

  /**
   * @brief Get the boolean value of the attribute.
   *
   * @return bool The current value of the attribute.
   */
  bool get_value() const { return this->value; }

  /**
   * @brief Set the boolean value of the attribute.
   *
   * @param new_value The new boolean value to set.
   */
  void set_value(const bool &new_value) { this->value = new_value; }

  /**
   * @brief Convert the boolean value to a string ("true" or "false").
   *
   * @return std::string The string representation of the boolean value.
   */
  std::string to_string() override { return this->value ? "true" : "false"; }

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
  bool        value;       /**< The boolean value of the attribute */
  std::string label_true;  /**< The label describing the true state */
  std::string label_false; /**< The label describing the false state */
};

} // namespace attr