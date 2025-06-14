/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file cloud_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QWheelEvent>
#include <QWidget>

#include "attributes/path_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class PathCanvasWidget : public QWidget
{
  Q_OBJECT

public:
  PathCanvasWidget() = delete;

  PathCanvasWidget(PathAttribute *p_attr, QWidget *parent = nullptr);

  void clear();

  void load_from_csv();

  void randomize();

  void reorder_nns();

  void reverse();

  void update_widget_from_attribute();

Q_SIGNALS:
  void value_changed();

protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

  void wheelEvent(QWheelEvent *event) override;

private:
  PathAttribute *p_attr;

  float margin;

  float radius;

  std::vector<QPointF> qpoints = {};

  std::vector<float> qvalues = {};

  int moving_point_index = -1;

  int hovered_edge_index = -1;

  QPointF map_to_value(const QPointF &widget_point);

  QPointF map_to_widget(const QPointF &value_point);

  int get_hovered_point_index(const QPointF &pos);

  int get_hovered_edge_index(const QPointF &pos);

  void update_attribute_from_widget();
};

class PathWidget : public AbstractWidget
{
  Q_OBJECT

public:
  PathWidget() = delete;

  PathWidget(PathAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false);

private:
  PathAttribute *p_attr;

  PathCanvasWidget *canvas;
};

} // namespace attr
