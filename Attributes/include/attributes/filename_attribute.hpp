/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file filename_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <filesystem>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

class FilenameAttribute : public AbstractAttribute
{
public:
  FilenameAttribute() = delete;

  FilenameAttribute(std::filesystem::path value,
                    std::string           filter = "",
                    std::string           label = "");

  std::string get_filter() const { return this->filter; }

  std::filesystem::path get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override;

  nlohmann::json json_to() const override;

  void set_value(const std::filesystem::path &new_value) { this->value = new_value; }

  std::string to_string() { return this->value.string(); }

private:
  std::filesystem::path value;
  std::string           filter;
};

} // namespace attr
