/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
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

  void set_point(float x, float y);

signals:
  void value_changed();

public slots:
  void center_point();
  void random_point();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  void    handle_mouse_event(const QPoint &widget_point);
  QPointF map_to_value(const QPointF &widget_point);
  QPointF map_to_widget(const QPointF &value_point);
  void    update_attribute_from_widget();

  Vec2FloatAttribute *p_attr;
  float               radius = 5.f;
  float               margin = 20.f;
  QPointF             point;
};

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
  Vec2FloatAttribute *p_attr;
  XYWidget           *xy_widget;
};

} // namespace attr
