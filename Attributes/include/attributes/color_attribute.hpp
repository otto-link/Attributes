/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a color attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the `ColorAttribute` class, which represents
 * an attribute that stores a color value as a vector of floats. The class provides
 * functionality for setting and getting the color value, JSON serialization and
 * deserialization, and converting the color value to a string representation.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class ColorAttribute
 * @brief A class representing a color attribute derived from `AbstractAttribute`.
 *
 * The `ColorAttribute` class manages attributes that represent RGBA color values,
 * stored as a vector of four floats. It provides methods to:
 * - Set and get the color value.
 * - Serialize and deserialize the attribute to/from JSON.
 * - Convert the color value to a string representation.
 *
 * The default color value is white (1.0, 1.0, 1.0, 1.0).
 */
class ColorAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructs a `ColorAttribute` with a label and an initial RGBA color value.
   *
   * Initializes the color value with a vector of four floats representing the RGBA
   * components and associates a label with the attribute.
   *
   * @param label A label describing the attribute.
   * @param value A vector of four floats representing the RGBA color (red, green, blue,
   * alpha).
   */
  ColorAttribute(const std::string &label, const std::vector<float> &value);

  /**
   * @brief Constructs a `ColorAttribute` with a label and individual RGBA components.
   *
   * Initializes the color value using individual red, green, blue, and alpha components.
   *
   * @param label A label describing the attribute.
   * @param r The red component of the color (0.0 to 1.0).
   * @param g The green component of the color (0.0 to 1.0).
   * @param b The blue component of the color (0.0 to 1.0).
   * @param a The alpha (transparency) component of the color (0.0 to 1.0).
   */
  ColorAttribute(const std::string &label,
                 const float        r,
                 const float        g,
                 const float        b,
                 const float        a);

  /**
   * @brief Gets the current RGBA color value of the attribute.
   *
   * @return std::vector<float> A vector of four floats representing the RGBA color value.
   */
  std::vector<float> get_value() const { return this->value; }

  /**
   * @brief Sets the RGBA color value of the attribute.
   *
   * Updates the color value with a new vector of four floats representing the RGBA
   * components.
   *
   * @param new_value A vector of four floats representing the new RGBA color value.
   */
  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  /**
   * @brief Deserializes the attribute from a JSON object.
   *
   * Loads the attribute's state, including its RGBA value, from the provided JSON object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serializes the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current RGBA value.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Converts the color value to a string representation.
   *
   * Returns the color value as a formatted string in the form "r, g, b, a".
   *
   * @return std::string The string representation of the color value.
   */
  std::string to_string();

private:
  std::vector<float> value = {
      1.f,
      1.f,
      1.f,
      1.f}; /**< The RGBA color value, defaulting to white (1.0, 1.0, 1.0, 1.0). */
};

} // namespace attr