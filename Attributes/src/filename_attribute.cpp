/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/filename_attribute.hpp"

namespace attr
{

FilenameAttribute::FilenameAttribute(std::filesystem::path value,
                                     bool                  for_saving,
                                     std::string           filter,
                                     std::string           label)
    : AbstractAttribute(AttributeType::FILENAME, label, BoundCheck::UNCHECKED),
      value(value), for_saving(for_saving), filter(filter)
{
}

void FilenameAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::filesystem::path>();
  this->for_saving = json["for_saving"];
  this->filter = json["filter"];
  this->label = json["label"];
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

} // namespace attr
