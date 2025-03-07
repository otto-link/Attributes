/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file wave_nb_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines an attribute for handling wave numbers with optional linked X and Y
 * values.
 *
 * This file contains the definition of the WaveNbAttribute class, which represents an
 * attribute used to manage wave numbers for operations in X and Y dimensions.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class WaveNbAttribute
 * @brief A class representing wave number attributes with bounds and optional X/Y
 * linkage.
 *
 * WaveNbAttribute stores wave number values as a vector of floats and allows setting
 * bounds. It includes an option to link the X and Y values, ensuring that they stay
 * synchronized.
 */
class WaveNbAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the attribute with default values.
   */
  WaveNbAttribute();

  /**
   * @brief Constructs a WaveNbAttribute with specific values and bounds.
   *
   * Initializes the attribute with a vector of wave numbers, bounds for X and Y, and
   * an optional flag to link the X and Y values.
   *
   * @param value A vector containing wave numbers.
   * @param vmin The minimum value for the wave number.
   * @param vmax The maximum value for the wave number.
   * @param link_xy A boolean flag indicating whether to link the X and Y values.
   * @param label An optional label for the attribute.
   * @param bound_check The type of bound checking to apply, default is LOWER_ONLY.
   */
  WaveNbAttribute(std::vector<float> value,
                  float              vmin,
                  float              vmax,
                  bool               link_xy = true,
                  const std::string &label = "");

  /**
   * @brief Get the link_xy flag.
   *
   * @return bool Whether the X and Y values are linked.
   */
  bool get_link_xy() const { return this->link_xy; }

  /**
   * @brief Get the wave number values.
   *
   * @return std::vector<float> The current vector of wave number values.
   */
  std::vector<float> get_value() const { return this->value; }

  /**
   * @brief Get the minimum bound for the wave number.
   *
   * @return float The minimum wave number value.
   */
  float get_vmin() const { return this->vmin; }

  /**
   * @brief Get the maximum bound for the wave number.
   *
   * @return float The maximum wave number value.
   */
  float get_vmax() const { return this->vmax; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including wave numbers and bounds, from a JSON object.
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

  /**
   * @brief Set the link_xy flag.
   *
   * Updates the link_xy flag, which determines whether the X and Y wave numbers are
   * linked.
   *
   * @param new_state The new state of the link_xy flag.
   */
  void set_link_xy(const bool new_state) { this->link_xy = new_state; }

  /**
   * @brief Set the wave number values.
   *
   * Updates the wave number values with a new vector of floats.
   *
   * @param new_value A vector containing the new wave number values.
   */
  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  /**
   * @brief Convert the wave number values to a string representation.
   *
   * @return std::string A string representing the current wave number values.
   */
  std::string to_string();

private:
  std::vector<float> value;   /**< A vector containing the wave numbers. */
  float              vmin;    /**< The minimum bound for the wave numbers. */
  float              vmax;    /**< The maximum bound for the wave numbers. */
  bool               link_xy; /**< Whether the X and Y wave numbers are linked. */
};

} // namespace attr
