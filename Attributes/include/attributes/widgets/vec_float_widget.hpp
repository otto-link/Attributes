/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file vec_float_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QMouseEvent>
#include <QWidget>

#include "attributes/vec_float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class FVecWidget : public QWidget
{
  Q_OBJECT

public:
  FVecWidget() = delete;

  FVecWidget(VecFloatAttribute *p_attr, QWidget *parent = nullptr);

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
  VecFloatAttribute *p_attr;

  float radius;

  int moving_point_index = -1;

  std::vector<QPointF> qpoints = {};

  int get_hovered_point_index(const QPointF &pos);

  float map_ypos_to_value(float ypos);

  float map_value_to_ypos(float value);
};

class VecFloatWidget : public AbstractWidget
{
public:
  VecFloatWidget() = delete;

  VecFloatWidget(VecFloatAttribute *p_attr);

  void reset_value() override;

private:
  VecFloatAttribute *p_attr;

  FVecWidget *vec_widget;
};

} // namespace attr
