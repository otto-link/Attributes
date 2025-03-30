/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file choice_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a choice attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the ChoiceAttribute class, which represents
 * an attribute that stores a value selected from a predefined list of choices.
 * The class provides functions for setting and getting the selected value,
 * JSON serialization/deserialization, and managing the list of choices.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class ChoiceAttribute
 * @brief A class representing a choice attribute.
 *
 * ChoiceAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent a selection from a predefined list of choices. It provides methods
 * to access and modify the selected value, serialize and deserialize to/from JSON,
 * and manage the list of available choices.
 */
class ChoiceAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a ChoiceAttribute with a list of choices and a
   * value.
   *
   * @param choice_list The list of available choices.
   * @param value The initial selected value from the choice list.
   */
  ChoiceAttribute(const std::vector<std::string> &choice_list, const std::string &value);

  /**
   * @brief Constructor to initialize a ChoiceAttribute with a label, list of choices, and
   * a value.
   *
   * @param label The label describing the attribute.
   * @param choice_list The list of available choices.
   * @param value The initial selected value from the choice list.
   */
  ChoiceAttribute(const std::string              &label,
                  const std::vector<std::string> &choice_list,
                  const std::string              &value);

  /**
   * @brief Constructor to initialize a ChoiceAttribute with a label and a list of
   * choices.
   *
   * The initial value is set to the first item in the choice list.
   *
   * @param label The label describing the attribute.
   * @param choice_list The list of available choices.
   */
  ChoiceAttribute(const std::string &label, const std::vector<std::string> &choice_list);

  /**
   * @brief Convert the selected value to a string.
   *
   * @return std::string The string representation of the selected value.
   */
  std::vector<std::string> get_choice_list() const { return this->choice_list; }

  /**
   * @brief Get the currently selected value of the attribute.
   *
   * @return std::string The current selected value.
   */
  std::string get_value() const { return this->value; }

  /**
   * @brief Set the list of choice.
   *
   * @param new_choice_list The new value to set.
   */
  void set_choice_list(const std::vector<std::string> &new_choice_list)
  {
    this->choice_list = new_choice_list;
  };

  /**
   * @brief Set the selected value of the attribute.
   *
   * @param new_value The new value to set. Must be one of the choices in the choice list.
   */
  void set_value(const std::string &new_value) { this->value = new_value; }

  /**
   * @brief Convert the selected value to a string.
   *
   * @return std::string The string representation of the selected value.
   */
  std::string to_string() override;

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state (selected value and choice list) from a provided JSON
   * object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * @return nlohmann::json A JSON object representing the attribute's current state,
   * including the selected value and the list of choices.
   */
  nlohmann::json json_to() const override;

private:
  std::string              value; /**< The currently selected value of the attribute. */
  std::vector<std::string> choice_list; /**< The list of available choices. */
};

} // namespace attr
