/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file filename_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief Defines a filename attribute class derived from AbstractAttribute.
 *
 * This file contains the definition of the FilenameAttribute class, which represents
 * an attribute that stores a file path and optional filter. The class provides functions
 * for setting and getting the file path value, JSON serialization/deserialization,
 * and string conversion of the path.
 *
 * @copyright Copyright (c) 2024 Otto Link
 */

#pragma once
#include <filesystem>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

/**
 * @class FilenameAttribute
 * @brief A class representing a filename attribute.
 *
 * FilenameAttribute is derived from AbstractAttribute and is used to manage attributes
 * that represent file paths. It provides methods to access and modify the file path,
 * set filters for file types, serialize and deserialize to/from JSON, and convert
 * the file path to a string.
 */
class FilenameAttribute : public AbstractAttribute
{
public:
  /**
   * @brief Constructor to initialize a FilenameAttribute with a file path, filter, and
   * label.
   *
   * @param value The file path associated with the attribute.
   * @param filter A string representing a file type filter (optional, default is empty).
   * @param label A label describing the attribute (optional, default is empty).
   */
  FilenameAttribute(std::filesystem::path value,
                    std::string           filter = "",
                    std::string           label = "");

  /**
   * @brief Get the file type filter of the attribute.
   *
   * Returns the filter string, which may limit the types of files that can be selected.
   *
   * @return std::string The file type filter.
   */
  std::string get_filter() const { return this->filter; }

  /**
   * @brief Get the file path value of the attribute.
   *
   * Returns the file path currently stored in the attribute.
   *
   * @return std::filesystem::path The file path.
   */
  std::filesystem::path get_value() const { return this->value; }

  /**
   * @brief Set the file path value of the attribute.
   *
   * Updates the file path with a new value.
   *
   * @param new_value The new file path to set.
   */
  void set_value(const std::filesystem::path &new_value) { this->value = new_value; }

  /**
   * @brief Deserialize the attribute from a JSON object.
   *
   * Loads the attribute's state, including the file path and filter, from a provided JSON
   * object.
   *
   * @param json The JSON object containing the attribute data.
   */
  void json_from(nlohmann::json const &json) override;

  /**
   * @brief Serialize the attribute to a JSON object.
   *
   * Generates a JSON representation of the attribute's current state, including the file
   * path.
   *
   * @return nlohmann::json A JSON object representing the attribute's state.
   */
  nlohmann::json json_to() const override;

  /**
   * @brief Convert the file path value to a string representation.
   *
   * Returns the file path as a string.
   *
   * @return std::string The string representation of the file path.
   */
  std::string to_string() { return this->value.string(); }

private:
  std::filesystem::path value;  /**< The file path associated with the attribute */
  std::string           filter; /**< A filter string to limit the types of files */
};

} // namespace attr
