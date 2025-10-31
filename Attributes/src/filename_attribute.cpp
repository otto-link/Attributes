/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/filename_attribute.hpp"

namespace attr
{

FilenameAttribute::FilenameAttribute(const std::string           &label,
                                     const std::filesystem::path &value,
                                     const std::string           &filter,
                                     const bool                   for_saving)
    : AbstractAttribute(AttributeType::FILENAME, label), value(value),
      for_saving(for_saving), filter(filter)
{
  this->save_state();
  this->save_initial_state();
}

std::string FilenameAttribute::get_filter() const { return this->filter; }

bool FilenameAttribute::get_for_saving() const { return this->for_saving; };

std::filesystem::path FilenameAttribute::get_value() const { return this->value; }

void FilenameAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get<std::filesystem::path>(json, "value", value);
  json_safe_get(json, "for_saving", for_saving);
  json_safe_get(json, "filter", filter);
  json_safe_get(json, "label", label);
}

nlohmann::json FilenameAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["for_saving"] = this->for_saving;
  json["filter"] = this->filter;
  json["label"] = this->label;
  return json;
}

void FilenameAttribute::set_value(const std::filesystem::path &new_value)
{
  this->value = new_value;
}

std::string FilenameAttribute::to_string() { return this->value.string(); }

} // namespace attr
