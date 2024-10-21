/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec_int_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class VecIntAttribute : public AbstractAttribute
{
public:
  VecIntAttribute(std::vector<int> value, int vmin, int vmax, const std::string &label);

  std::vector<int> get_value() const { return this->value; }

  std::vector<int> *get_value_ref() { return &this->value; }

  /**
   * @brief Get the minimum bound of the attribute.
   *
   * Returns the minimum bound for the int value, if bounds checking is enabled.
   *
   * @return int The minimum bound.
   */
  int get_vmin() const { return this->vmin; }

  /**
   * @brief Get the maximum bound of the attribute.
   *
   * Returns the maximum bound for the int value, if bounds checking is enabled.
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

  void set_value(const std::vector<int> &new_value) { this->value = new_value; }

  /**
   * @brief Convert the int value to a string representation.
   *
   * Returns the int value as a string.
   *
   * @return std::string The string representation of the int value.
   */
  std::string to_string();

private:
  std::vector<int> value; /**< The vector of inting-point value of the attribute */
  int              vmin;  /**< The minimum bound for the int value */
  int              vmax;  /**< The maximum bound for the int value */
};

} // namespace attr
