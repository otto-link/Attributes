/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec2float_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a 2D vector attribute (Vec2Float) for handling two float values.
 *
 * This file contains the definition of the Vec2FloatAttribute class, which represents
 * an attribute that stores a 2D vector (pair of float values) and supports bound
 * checking.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class Vec2FloatAttribute
 * @brief A class representing a 2D vector attribute with float values and bounds.
 *
 * Vec2FloatAttribute is derived from AbstractAttribute and is used to manage two float
 * values that represent a 2D vector. It includes functionality for setting and getting
 * values, as well as optional bounds for the X and Y components.
 */
class Vec2FloatAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Deleted default constructor.
   *
   * The default constructor is deleted to enforce initialization with specific values.
   */
  Vec2FloatAttribute() = delete;

  /**
   * @brief Constructs a Vec2FloatAttribute with a label.
   *
   * Initializes the attribute with a label but no initial values.
   *
   * @param label The label for the attribute.
   */
  Vec2FloatAttribute(const std::string &label);

  /**
   * @brief Constructs a Vec2FloatAttribute with specific values and bounds.
   *
   * @param value A vector containing two float values representing X and Y.
   * @param xmin The minimum bound for the X component.
   * @param xmax The maximum bound for the X component.
   * @param ymin The minimum bound for the Y component.
   * @param ymax The maximum bound for the Y component.
   * @param label Optional label for the attribute.
   */
  Vec2FloatAttribute(std::vector<float> value,
                     float              xmin,
                     float              xmax,
                     float              ymin,
                     float              ymax,
                     const std::string &label = "");

  /**
   * @brief Get the bound checking mode.
   *
   * @return BoundCheck The current bound check mode.
   */
  BoundCheck get_bound_check() const { return this->bound_check; }

  /**
   * @brief Get the current 2D vector value.
   *
   * @return std::vector<float> The current vector of two float values (X, Y).
   */
  std::vector<float> get_value() const { return this->value; }

  /**
   * @brief Get the minimum bound for the X component.
   *
   * @return float The minimum X value.
   */
  float get_xmin() const { return this->xmin; }

  /**
   * @brief Get the maximum bound for the X component.
   *
   * @return float The maximum X value.
   */
  float get_xmax() const { return this->xmax; }

  /**
   * @brief Get the minimum bound for the Y component.
   *
   * @return float The minimum Y value.
   */
  float get_ymin() const { return this->ymin; }

  /**
   * @brief Get the maximum bound for the Y component.
   *
   * @return float The maximum Y value.
   */
  float get_ymax() const { return this->ymax; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including its 2D vector and bounds, from a JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including its
   * 2D vector and bounds.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Set the 2D vector value.
   *
   * Updates the 2D vector value with a new pair of float values.
   *
   * @param new_value A vector containing the new X and Y values.
   */
  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  /**
   * @brief Convert the 2D vector value to a string representation.
   *
   * @return std::string A string representing the current X and Y values.
   */
  std::string to_string();

private:
  std::vector<float>
        value;      /**< A vector containing two float values representing X and Y */
  float xmin, xmax; /**< The bounds for the X component */
  float ymin, ymax; /**< The bounds for the Y component */
};

} // namespace attr
