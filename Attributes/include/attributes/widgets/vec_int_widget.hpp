/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec_int_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QMouseEvent>
#include <QWidget>

#include "attributes/vec_int_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class IVecWidget : public QWidget
{
  Q_OBJECT

public:
  IVecWidget() = delete;

  IVecWidget(VecIntAttribute *p_attr, QWidget *parent = nullptr);

  void update_widget_from_attribute();

Q_SIGNALS:
  void value_changed();

public Q_SLOTS:
  void new_value();

protected:
  void mouseMoveEvent(QMouseEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

  void update_attribute_from_widget();

private:
  VecIntAttribute *p_attr;

  int radius;

  int moving_point_index = -1;

  std::vector<QPointF> qpoints = {};

  int get_hovered_point_index(const QPointF &pos);

  int map_ypos_to_value(float ypos);

  float map_value_to_ypos(int value);
};

class VecIntWidget : public AbstractWidget
{
public:
  VecIntWidget() = delete;

  VecIntWidget(VecIntAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  VecIntAttribute *p_attr;

  IVecWidget *vec_widget;
};

} // namespace attr
