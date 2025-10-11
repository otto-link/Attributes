/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <functional>

#include <QImage>

#include "highmap/geometry/cloud.hpp"

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// CloudAttribute
// =====================================

class CloudAttribute : public AbstractAttribute
{
public:
  CloudAttribute(const std::string &label);
  CloudAttribute(const std::string &label, const hmap::Cloud &value);

  std::function<QImage()> get_background_image_fct() const;
  hmap::Cloud             get_value() const { return this->value; }
  hmap::Cloud            *get_value_ref() { return &this->value; }
  void                    set_background_image_fct(std::function<QImage()> new_fct);
  void        set_value(const hmap::Cloud &new_value) { this->value = new_value; }
  std::string to_string();

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

private:
  hmap::Cloud             value;
  std::function<QImage()> background_image_fct = nullptr;
};

} // namespace attr
