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
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

#include "attributes/cloud_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class CloudCanvasWidget : public QGraphicsView
{
  Q_OBJECT

public:
  CloudCanvasWidget() = delete;

  CloudCanvasWidget(CloudAttribute *p_attr, QWidget *parent = nullptr);

  void clear();

  void reset_scene();

Q_SIGNALS:
  void value_changed();

protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void wheelEvent(QWheelEvent *event) override;

private:
  CloudAttribute *p_attr;

  float radius = 20.f;
  float margin = 10.f;
  int   id_point_data = 0;

  QGraphicsEllipseItem *moving_point = nullptr;
  QPointF               offset;

  void add_point(QPointF event_pos, float point_value = 1.f);

  void clear_scene();

  void update_attribute_from_widget();

  void update_point_colors();

  void update_scene();
};

class CloudWidget : public AbstractWidget
{
  Q_OBJECT

public:
  CloudWidget() = delete;

  CloudWidget(CloudAttribute *p_attr);

private:
  CloudAttribute *p_attr;

  QImage array_to_image();

  void smooth_array();
};

} // namespace attr
