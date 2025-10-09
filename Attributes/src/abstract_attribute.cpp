/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/abstract_attribute.hpp"

namespace attr
{

AbstractAttribute::AbstractAttribute(const AttributeType &type, const std::string &label)
    : type(type), label(label)
{
}

std::string AbstractAttribute::get_label() const { return this->label; }

AttributeType AbstractAttribute::get_type() const { return this->type; }

std::string AbstractAttribute::get_type_string() const
{
  if (attribute_type_map.contains(this->type))
    return attribute_type_map.at(this->type);
  else
    return "INVALID TYPE";
}

void AbstractAttribute::json_from(nlohmann::json const &json)
{
  this->type = json["type"].get<AttributeType>();
  this->label = json["label"];
}

nlohmann::json AbstractAttribute::json_to() const
{
  nlohmann::json json;
  json["type"] = this->type;
  json["type_string"] = attribute_type_map.at(this->type);
  json["label"] = this->label;
  return json;
}

void AbstractAttribute::reset_to_initial_state()
{
  if (this->attribute_initial_state.is_null())
  {
    Logger::log()->error("AbstractAttribute::reset_to_initial_state: empty saved state, "
                         "could not reset attribute state. attribute label: {}",
                         this->label);
    return;
  }

  this->json_from(this->attribute_initial_state);
}

void AbstractAttribute::reset_to_save_state()
{
  if (this->attribute_state.is_null())
  {
    Logger::log()->error("AbstractAttribute::reset_to_save_state: empty saved state, "
                         "could not reset attribute state. attribute label: {}",
                         this->label);
  }
  else
  {
    // actually switch current state and save state to allow
    // "toggling" between the two states when resetting the state
    nlohmann::json current_state = this->json_to();

    // restore
    this->json_from(this->attribute_state);

    // current to backup
    this->attribute_state = current_state;
  }
}

void AbstractAttribute::save_initial_state()
{
  // serialize current state
  this->attribute_initial_state = this->json_to();
}

void AbstractAttribute::save_state()
{
  // serialize current state
  this->attribute_state = this->json_to();
}

void AbstractAttribute::set_label(const std::string &new_label)
{
  this->label = new_label;
}

} // namespace attr
