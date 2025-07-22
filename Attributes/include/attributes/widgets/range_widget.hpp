/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file range_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QPushButton>

#include "qsx/slider_range.hpp"

#include "attributes/range_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

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
  RangeAttribute    *p_attr;
  qsx::SliderRange  *slider;
  std::vector<float> value_bckp;

  void update_attribute_from_widget();
};

} // namespace attr
