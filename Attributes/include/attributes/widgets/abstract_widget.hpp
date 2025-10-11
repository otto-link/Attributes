/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <functional>

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

  virtual void reset_value(bool /*reset_to_initial_state*/ = false) = 0;

  void set_tool_tip_fct(std::function<std::string()> new_fct);

signals:
  void value_changed();

protected:
  bool event(QEvent *event) override; // tooltip override

private:
  std::function<std::string()> tool_tip_fct = nullptr;
};

} // namespace attr
