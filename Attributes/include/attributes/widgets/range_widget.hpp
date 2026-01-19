/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QPushButton>

#include "qsx/slider_range.hpp"

#include "attributes/range_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// RangeWidget
// =====================================

class RangeWidget : public AbstractWidget
{
  Q_OBJECT

public:
  RangeWidget() = delete;
  RangeWidget(RangeAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

signals:
  void update_bins();

private:
  void update_attribute_from_widget();

  RangeAttribute   *p_attr;
  qsx::SliderRange *slider;
  glm::vec2         value_bckp;
};

} // namespace attr
