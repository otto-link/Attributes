/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QWidget>

#include "attributes/logger.hpp"

#define CANVAS_WIDTH 384
#define CANVAS_BGCOLOR QColor(42, 42, 42, 255)
#define CANVAS_MARGIN 20
#define CANVAS_POINT_RADIUS 5

namespace attr
{

// =====================================
// AbstractWidget
// =====================================

class AbstractWidget : public QWidget
{
  Q_OBJECT

public:
  AbstractWidget() = default;

  virtual void reset_value(bool /*reset_to_initial_state*/ = false)
  {
    Logger::log()->error("reset_value method not implemented");
  }

signals:
  void value_changed();
};

} // namespace attr
