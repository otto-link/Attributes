/* Copyright (c) 2025 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/resolution_attribute.hpp"

namespace attr
{

ResolutionAttribute::ResolutionAttribute(const std::string &label,
                                         int                width,
                                         int                height,
                                         bool               keep_aspect_ratio,
                                         bool               power_of_two,
                                         std::string        value_format)
    : AbstractAttribute(AttributeType::RESOLUTION, label), width(width), height(height),
      keep_aspect_ratio(keep_aspect_ratio), power_of_two(power_of_two),
      value_format(value_format)
{
  this->update_aspect_ratio();
  this->save_state();
  this->save_initial_state();
}

int ResolutionAttribute::get_width() const { return this->width; }

int ResolutionAttribute::get_height() const { return this->height; }

bool ResolutionAttribute::get_keep_aspect_ratio() const
{
  return this->keep_aspect_ratio;
}

bool ResolutionAttribute::get_power_of_two() const { return this->power_of_two; }

std::pair<int, int> ResolutionAttribute::get_value() const
{
  return {this->width, this->height};
}

std::string ResolutionAttribute::get_value_format() const { return this->value_format; }

void ResolutionAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->width = json["width"];
  this->height = json["height"];
  this->keep_aspect_ratio = json["keep_aspect_ratio"];
  this->power_of_two = json["power_of_two"];
  this->update_aspect_ratio();
}

nlohmann::json ResolutionAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["width"] = this->width;
  json["height"] = this->height;
  json["keep_aspect_ratio"] = this->keep_aspect_ratio;
  json["power_of_two"] = this->power_of_two;
  return json;
}

int ResolutionAttribute::make_power_of_two(int value, bool return_upper) const
{
  if (value <= 0)
    return 1;

  int lower = 1;
  while ((lower << 1) <= value)
    lower <<= 1;

  int upper = lower << 1;

  return return_upper ? upper : lower;
}

void ResolutionAttribute::set_height(int h)
{
  if (this->power_of_two)
    h = this->make_power_of_two(h);

  if (this->keep_aspect_ratio && this->width > 0)
    this->width = static_cast<int>(h * this->aspect_ratio);

  this->height = std::max(1, h);
  this->update_aspect_ratio();
}

void ResolutionAttribute::set_keep_aspect_ratio(bool enabled)
{
  this->keep_aspect_ratio = enabled;
  if (enabled)
    this->update_aspect_ratio();
}

void ResolutionAttribute::set_power_of_two(bool enabled)
{
  this->power_of_two = enabled;
  if (enabled)
  {
    this->width = make_power_of_two(this->width);
    this->height = make_power_of_two(this->height);
  }
}

void ResolutionAttribute::set_value(int w, int h)
{
  this->width = w;
  this->height = h;
}

void ResolutionAttribute::set_width(int w)
{
  if (this->power_of_two)
    w = this->make_power_of_two(w);

  if (this->keep_aspect_ratio && this->height > 0)
    this->height = static_cast<int>(w / this->aspect_ratio);

  this->width = std::max(1, w);
  this->update_aspect_ratio();
}

std::string ResolutionAttribute::to_string()
{
  return std::to_string(this->width) + "x" + std::to_string(this->height) +
         (this->power_of_two ? " (POT)" : "") + (this->keep_aspect_ratio ? " (AR)" : "");
}

void ResolutionAttribute::update_aspect_ratio()
{
  if (this->height != 0)
    this->aspect_ratio = static_cast<float>(this->width) /
                         static_cast<float>(this->height);
}

} // namespace attr
