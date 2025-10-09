/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/range_attribute.hpp"

namespace attr
{

RangeAttribute::RangeAttribute()
    : AbstractAttribute(AttributeType::RANGE, "Range"), value({0.f, 1.f}), vmin(-1.f),
      vmax(2.f), is_active(true), value_format("{:.3f}")
{
  this->save_state();
  this->save_initial_state();
}

RangeAttribute::RangeAttribute(const std::string &label, const bool is_active)
    : AbstractAttribute(AttributeType::RANGE, label), value({0.f, 1.f}), vmin(-1.f),
      vmax(2.f), is_active(is_active), value_format("{:.3f}")
{
  this->save_state();
  this->save_initial_state();
}

RangeAttribute::RangeAttribute(const std::string        &label,
                               const std::vector<float> &value,
                               const float               vmin,
                               const float               vmax,
                               const bool                is_active,
                               std::string               value_format)
    : AbstractAttribute(AttributeType::RANGE, label), value(value), vmin(vmin),
      vmax(vmax), is_active(is_active), value_format(value_format)
{
  this->save_state();
  this->save_initial_state();
}

bool RangeAttribute::get_autorange() const { return this->autorange; }

std::function<PairVec()> RangeAttribute::get_histogram_fct() const
{
  return this->histogram_fct;
}

bool RangeAttribute::get_is_active() const { return this->is_active; }

std::vector<float> RangeAttribute::get_value() const { return this->value; }

std::string RangeAttribute::get_value_format() const { return this->value_format; }

float RangeAttribute::get_vmin() const { return this->vmin; }

float RangeAttribute::get_vmax() const { return this->vmax; }

void RangeAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"].get<std::vector<float>>();
  this->vmin = json["vmin"];
  this->vmax = json["vmax"];
  this->is_active = json["is_active"];
}

nlohmann::json RangeAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["vmin"] = this->vmin;
  json["vmax"] = this->vmax;
  json["is_active"] = this->is_active;
  return json;
}

void RangeAttribute::set_autorange(bool new_state) { this->autorange = new_state; }

void RangeAttribute::set_histogram_fct(std::function<PairVec()> new_histogram_fct)
{
  this->histogram_fct = new_histogram_fct;
}

void RangeAttribute::set_is_active(bool new_state) { this->is_active = new_state; }

void RangeAttribute::set_value(const std::vector<float> &new_value)
{
  this->value = new_value;
}

std::string RangeAttribute::to_string()
{
  std::string str = "{";
  str += std::to_string(this->value[0]);
  str += ", ";
  str += std::to_string(this->value[1]);
  str += "}";
  return str;
}

} // namespace attr
