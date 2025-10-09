/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <filesystem>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// FilenameAttribute
// =====================================

class FilenameAttribute : public AbstractAttribute
{
public:
  FilenameAttribute(const std::string           &label,
                    const std::filesystem::path &value,
                    const std::string           &filter = "",
                    const bool                   for_saving = true);

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  std::string           get_filter() const;
  bool                  get_for_saving() const;
  std::filesystem::path get_value() const;
  void                  set_value(const std::filesystem::path &new_value);
  std::string           to_string() override;

private:
  // for_saving: whether the filename is used for loading or saving (change the widget
  // behavior)
  std::filesystem::path value;
  bool                  for_saving;
  std::string           filter;
};

} // namespace attr
