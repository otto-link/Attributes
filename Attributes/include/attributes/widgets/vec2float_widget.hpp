/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec2float_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <random>

#include <QMouseEvent>
#include <QWidget>

#include "attributes/vec2float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class XYWidget : public QWidget
{
  Q_OBJECT

public:
  XYWidget() = delete;

  XYWidget(Vec2FloatAttribute *p_attr);

Q_SIGNALS:
  void value_changed();

public Q_SLOTS:
  void center_point();

  void random_point();

protected:
  void paintEvent(QPaintEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  Vec2FloatAttribute *p_attr;

  float radius = 5.f;
  float margin = 20.f;

  QPointF point;

  // Handle mouse events and update the vector's value based on the mouse position
  void handle_mouse_event(const QPoint &widget_point);

  // Map the point from the widget coordinates to the (xmin, xmax, ymin, ymax) coordinate
  // system
  QPointF map_to_value(const QPointF &widget_point);

  // Map the point from the (xmin, xmax, ymin, ymax) coordinate system to the widget
  // coordinates
  QPointF map_to_widget(const QPointF &value_point);

  void set_point(float x, float y);

  void update_attribute_from_widget();
};

class Vec2FloatWidget : public AbstractWidget
{
public:
  Vec2FloatWidget() = delete;

  Vec2FloatWidget(Vec2FloatAttribute *p_attr);

private:
  Vec2FloatAttribute *p_attr;

  XYWidget *xy_widget;
};

} // namespace attr
