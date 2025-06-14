/**
 * @file abstract_widget.hpp
 * @author
 * Otto Link (otto.link.bv@gmail.com)
 *
 * @brief
 * This file defines the AbstractWidget class, which serves as a base class
 * for creating custom Qt widgets that emit a signal when their value changes.
 *
 * The AbstractWidget class inherits from QWidget and provides a default
 * constructor. The signal `value_changed()` is emitted when the widget's value
 * is modified, making it useful for integrating with signal-slot mechanisms
 * in Qt-based applications.
 *
 * @copyright
 * Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software.
 *
 */

#pragma once
#include <QWidget>

#include "attributes/logger.hpp"

#define CANVAS_WIDTH 384
#define CANVAS_BGCOLOR QColor(42, 42, 42, 255)
#define CANVAS_MARGIN 20
#define CANVAS_POINT_RADIUS 5

namespace attr
{

/**
 * @class AbstractWidget
 * @brief A base class for custom Qt widgets that emit a value change signal.
 *
 * AbstractWidget is a simple QWidget-based class that emits the `value_changed()`
 * signal whenever the value within the widget changes. It can be extended by
 * other widgets to add custom behavior, while maintaining the signal mechanism
 * for external communication within a Qt application.
 *
 * @note The class is part of the attr namespace.
 */
class AbstractWidget : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Default constructor for AbstractWidget.
   *
   * Creates an AbstractWidget instance with default settings.
   */
  AbstractWidget() = default;

  // TODO = 0
  virtual void reset_value(bool /*reset_to_initial_state*/ = false)
  {
    Logger::log()->error("reset_value method not implemented");
  }

Q_SIGNALS:
  /**
   * @brief Signal emitted when the widget's value changes.
   *
   * This signal can be connected to other objects in a Qt application to
   * respond when the widget's internal value changes.
   */
  void value_changed();
};

} // namespace attr
