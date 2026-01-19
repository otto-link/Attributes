/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/wave_nb_attribute.hpp"

namespace attr
{

WaveNbAttribute::WaveNbAttribute()
    : AbstractAttribute(AttributeType::WAVE_NB, "Wavenumber"), value({2.f, 2.f}),
      vmin(0.f), vmax(FLT_MAX), link_xy(true), value_format("{:.2f}")
{
  this->save_state();
  this->save_initial_state();
}

WaveNbAttribute::WaveNbAttribute(const std::string &label)
    : AbstractAttribute(AttributeType::WAVE_NB, label), value({2.f, 2.f}), vmin(0.f),
      vmax(FLT_MAX), link_xy(true), value_format("{:.2f}")
{
  this->save_state();
  this->save_initial_state();
}

WaveNbAttribute::WaveNbAttribute(const std::string &label,
                                 const glm::vec2   &value,
                                 const float        vmin,
                                 const float        vmax,
                                 const bool         link_xy,
                                 std::string        value_format)
    : AbstractAttribute(AttributeType::WAVE_NB, label), value(value), vmin(vmin),
      vmax(vmax), link_xy(link_xy), value_format(value_format)
{
  this->save_state();
  this->save_initial_state();
}

bool WaveNbAttribute::get_link_xy() const { return this->link_xy; }

glm::vec2 WaveNbAttribute::get_value() const { return this->value; }

std::string WaveNbAttribute::get_value_format() const { return this->value_format; }

float WaveNbAttribute::get_vmin() const { return this->vmin; }

float WaveNbAttribute::get_vmax() const { return this->vmax; }

void WaveNbAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  json_safe_get(json, "value", value);
  json_safe_get(json, "vmin", vmin);
  json_safe_get(json, "vmax", vmax);
  json_safe_get(json, "link_xy", link_xy);
}

nlohmann::json WaveNbAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = {this->value.x, this->value.y};
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  json["link_xy"] = this->link_xy;
  return json;
}

void WaveNbAttribute::set_link_xy(const bool new_state) { this->link_xy = new_state; }

void WaveNbAttribute::set_value(const glm::vec2 &new_value) { this->value = new_value; }

std::string WaveNbAttribute::to_string()
{
  std::string str = "{";
  str += std::to_string(this->value.x) + ", " + std::to_string(this->value.y);
  return str + "}";
}

} // namespace attr
