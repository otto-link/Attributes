/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <algorithm>
#include <vector>

#include <QImage>

#include "attributes/abstract_attribute.hpp"

namespace attr
{

// =====================================
// ArrayAttribute
// =====================================

class ArrayAttribute : public AbstractAttribute
{
public:
  ArrayAttribute(const std::string &label, const glm::ivec2 &shape);
  ArrayAttribute(const std::string        &label,
                 const glm::ivec2         &shape,
                 const std::vector<float> &vector);

  std::function<QImage()>   get_background_image_fct() const;
  glm::ivec2                get_shape() const { return this->shape; }
  const std::vector<float> &get_value() const { return this->vector; }
  std::vector<float>       *get_value_ref() { return &this->vector; }
  void                      set_background_image_fct(std::function<QImage()> new_fct);
  void        set_value(const std::vector<float> &new_value) { this->vector = new_value; }
  std::string to_string();

  void           json_from(nlohmann::json const &json) override;
  nlohmann::json json_to() const override;

private:
  glm::ivec2              shape;
  std::vector<float>      vector;
  std::function<QImage()> background_image_fct = nullptr;

  float min() const { return *std::min_element(vector.begin(), vector.end()); }
  float max() const { return *std::max_element(vector.begin(), vector.end()); }
};

} // namespace attr