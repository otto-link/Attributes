/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once

#include "highmap/kernels.hpp"

#include "qsx/canvas_field.hpp"

#include "attributes/array_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

#define DEFAULT_CANVAS_RESOLUTION 512

namespace attr
{

// =====================================
// ArrayWidget
// =====================================

class ArrayWidget : public AbstractWidget
{
  Q_OBJECT

public:
  ArrayWidget() = delete;
  ArrayWidget(ArrayAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

public slots:
  void on_canvas_edit_ended();

private:
  void array_data_to_widget_field_data();

  ArrayAttribute   *p_attr;
  qsx::CanvasField *canvas;
};

} // namespace attr
