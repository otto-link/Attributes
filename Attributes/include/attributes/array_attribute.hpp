/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file array_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "highmap/array.hpp"

#include "attributes/abstract_attribute.hpp"

namespace attr
{

class ArrayAttribute : public AbstractAttribute
{
public:
  ArrayAttribute(const std::string &label, const hmap::Vec2<int> &shape);

  ArrayAttribute(const hmap::Array &value, const std::string &label = "Array");

  hmap::Array get_value() const { return this->value; }

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
   * Generates a JSON representation of the attribute's current state.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  void set_value(const hmap::Array &new_value) { this->value = new_value; }

  /**
   * @brief Convert the hmap::Array value to a string representation.
   *
   * Returns the hmap::Array value as a string.
   *
   * @return std::string The string representation of the hmap::Array value.
   */
  std::string to_string();

private:
  hmap::Array value; /**< The hmap::Array value of the attribute */
};

} // namespace attr
