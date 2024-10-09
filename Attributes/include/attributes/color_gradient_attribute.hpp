/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_gradient_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines the ColorGradientAttribute class for representing and managing gradient
 * color attributes.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class ColorGradientAttribute
 * @brief Represents an attribute for managing color gradients.
 *
 * The ColorGradientAttribute class stores a collection of gradient color points, each
 * consisting of a position (x) and an RGBA color value. It allows serialization
 * to and from JSON, conversion to string, and setting or getting the gradient values.
 */
class ColorGradientAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructs a ColorGradientAttribute with a specified label.
   *
   * @param label The label for the attribute.
   */
  ColorGradientAttribute(const std::string &label);

  /**
   * @brief Constructs a ColorGradientAttribute with a specified gradient value and label.
   *
   * @param value A vector of vectors representing the gradient points, where each
   * point consists of (x, r, g, b, a).
   * @param label The label for the attribute.
   */
  ColorGradientAttribute(std::vector<std::vector<float>> value, const std::string &label);

  /**
   * @brief Retrieves the current gradient value.
   *
   * @return A vector of vectors representing the gradient points (x, r, g, b, a).
   */
  std::vector<std::vector<float>> get_value() const { return this->value; }

  std::vector<std::vector<float>> *get_value_ref() { return &this->value; }

  /**
   * @brief Sets a new gradient value.
   *
   * @param new_value A vector of vectors representing the new gradient points (x, r, g,
   * b, a).
   */
  void set_value(const std::vector<std::vector<float>> &new_value)
  {
    this->value = new_value;
  }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state from a provided JSON object, including its RGBA value.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current RGBA value.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Convert the value to a string representation.
   *
   * @return std::string The string representation of the value.
   */
  std::string to_string();

private:
  /**
   * @brief Stores the gradient value as a collection of points.
   *
   * Each point is represented as a vector of 5 floats: (x, r, g, b, a),
   * where x is the position on the gradient, and r, g, b, a represent the color values.
   */
  std::vector<std::vector<float>> value = {{0.f, 0.f, 0.f, 0.f, 1.f},
                                           {1.f, 0.f, 1.f, 0.f, 1.f}};
};

} // namespace attr
