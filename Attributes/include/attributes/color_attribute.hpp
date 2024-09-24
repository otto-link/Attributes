/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a color attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the ColorAttribute class, which represents
 * an attribute that stores a color value as a vector of floats. The class provides
 * functions for setting and getting the color value, JSON serialization/deserialization,
 * and string conversion of the color value.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class ColorAttribute
 * @brief A class representing a color attribute.
 *
 * ColorAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent RGBA color values stored as a vector of floats. It provides methods to
 * access and modify the color value, serialize and deserialize to/from JSON, and convert
 * the color to a string representation.
 */
class ColorAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a ColorAttribute with a color value and label.
   *
   * Initializes the color value with a vector of 4 floats (representing RGBA) and
   * associates a label with the attribute.
   *
   * @param value A vector of floats representing the RGBA color.
   * @param label A label describing the attribute.
   */
  ColorAttribute(std::vector<float> value, const std::string &label);

  /**
   * @brief Constructor to initialize a ColorAttribute with individual RGBA components and
   * a label.
   *
   * Initializes the color value using individual red, green, blue, and alpha components.
   *
   * @param r The red component of the color (0.0 to 1.0).
   * @param g The green component of the color (0.0 to 1.0).
   * @param b The blue component of the color (0.0 to 1.0).
   * @param a The alpha (transparency) component of the color (0.0 to 1.0).
   * @param label A label describing the attribute.
   */
  ColorAttribute(float r, float g, float b, float a, const std::string &label);

  /**
   * @brief Get the color value of the attribute.
   *
   * Returns the color value as a vector of 4 floats representing the RGBA components.
   *
   * @return std::vector<float> The RGBA color value.
   */
  std::vector<float> get_value() const { return this->value; }

  /**
   * @brief Set the color value of the attribute.
   *
   * Updates the color value with a new vector of RGBA floats.
   *
   * @param new_value A vector of floats representing the new RGBA color value.
   */
  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

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
   * @brief Convert the color value to a string representation.
   *
   * Returns the color value as a formatted string in the form "r, g, b, a".
   *
   * @return std::string The string representation of the color value.
   */
  std::string to_string();

private:
  std::vector<float> value =
      {1.f, 1.f, 1.f, 1.f}; /**< The RGBA color value, default is white (1,1,1,1) */
};

} // namespace attr
