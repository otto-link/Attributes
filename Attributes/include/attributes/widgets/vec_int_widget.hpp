/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QWidget>

#include "qsx/vector_editor.hpp"

#include "attributes/vec_int_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// VecIntWidget
// =====================================

class VecIntWidget : public AbstractWidget
{
public:
  VecIntWidget() = delete;
  VecIntWidget(VecIntAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void on_sampling_change(int sampling_points_variation);
  void update_attribute_from_widget();
  void update_widget_from_attribute();

  VecIntAttribute   *p_attr;
  qsx::VectorEditor *vector_editor;
};

} // namespace attr
