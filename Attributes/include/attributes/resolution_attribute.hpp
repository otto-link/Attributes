/* Copyright (c) 2025 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <utility>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

class ResolutionAttribute : public AbstractAttribute
{
public:
  ResolutionAttribute(const std::string &label,
                      int                width = 256,
                      int                height = 256,
                      bool               keep_aspect_ratio = true,
                      bool               power_of_two = true,
                      std::string        value_format = "{}");

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

  int  get_height() const;
  bool get_keep_aspect_ratio() const;
  bool get_power_of_two() const;
  int  get_width() const;
  int  make_power_of_two(int value, bool return_upper = false) const;
  void set_height(int h);
  void set_keep_aspect_ratio(bool enabled);
  void set_power_of_two(bool enabled);
  void set_width(int w);

  std::pair<int, int> get_value() const;
  std::string         get_value_format() const;
  void                set_value(int w, int h);
  std::string         to_string() override;

private:
  void update_aspect_ratio();

  int         width;
  int         height;
  bool        keep_aspect_ratio;
  bool        power_of_two;
  float       aspect_ratio;
  std::string value_format;
};

} // namespace attr
