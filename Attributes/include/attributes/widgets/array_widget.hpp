/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file array_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "highmap/kernels.hpp"

#include "qsx/canvas_field.hpp"

#include "attributes/array_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

#define DEFAULT_CANVAS_RESOLUTION 512

namespace attr
{

class ArrayWidget : public AbstractWidget
{
  Q_OBJECT

public:
  ArrayWidget() = delete;
  ArrayWidget(ArrayAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

public Q_SLOTS:
  void on_canvas_edit_ended();

private:
  void array_data_to_widget_field_data();

  ArrayAttribute   *p_attr;
  qsx::CanvasField *canvas;
};

} // namespace attr
