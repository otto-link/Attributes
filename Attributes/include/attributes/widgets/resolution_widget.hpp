/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QWidget>

#include "qsx/slider_int.hpp"

#include "attributes/resolution_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class ResolutionWidget : public AbstractWidget
{
public:
  explicit ResolutionWidget(ResolutionAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;
  void update_attribute_from_widget();
  void update_widget_from_attribute();

private:
  ResolutionAttribute *p_attr;
  qsx::SliderInt      *slider_width;
  qsx::SliderInt      *slider_height;
};

} // namespace attr
