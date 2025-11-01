/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <random>

#include <QMouseEvent>
#include <QWidget>

#include "qsx/point2d_selector.hpp"

#include "attributes/vec2float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// Vec2FloatWidget
// =====================================

class Vec2FloatWidget : public AbstractWidget
{
public:
  Vec2FloatWidget() = delete;
  Vec2FloatWidget(Vec2FloatAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void on_center();
  void on_randomize();
  void update_attribute_from_widget();

  Vec2FloatAttribute   *p_attr;
  qsx::Point2DSelector *point2d_selector;
};

} // namespace attr
