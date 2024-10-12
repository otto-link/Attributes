/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file seed_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a seed attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the SeedAttribute class, which represents
 * an attribute that stores a seed value for random number generation.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

typedef unsigned int uint;

namespace attr
{

/**
 * @class SeedAttribute
 * @brief A class representing a seed attribute for random number generation.
 *
 * The SeedAttribute class is derived from AbstractAttribute and is used to manage
 * seed values, typically for random number generation purposes. It provides methods
 * to get and set the seed value, as well as JSON serialization/deserialization.
 */
class SeedAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Default constructor.
   *
   * Initializes a SeedAttribute with a default seed value.
   */
  SeedAttribute();

  /**
   * @brief Constructor to initialize a SeedAttribute with a value and label.
   *
   * @param value The seed value (unsigned integer).
   * @param label The label describing the attribute.
   */
  SeedAttribute(uint value, const std::string &label);

  /**
   * @brief Get the current seed value.
   *
   * @return uint The current seed value.
   */
  uint get_value() const { return this->value; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including its seed value from a provided JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including its seed
   * value.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Set the seed value.
   *
   * Updates the seed value with a new value.
   *
   * @param new_value The new seed value (unsigned integer).
   */
  void set_value(const uint &new_value) { this->value = new_value; }

  /**
   * @brief Convert the current seed value to a string representation.
   *
   * Returns the current seed value as a string.
   *
   * @return std::string The string representation of the current seed value.
   */
  std::string to_string() { return std::to_string(this->value); }

private:
  uint value; /**< The current seed value */
};

} // namespace attr
