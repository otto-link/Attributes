/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QWidget>

#include "qsx/vector_editor.hpp"

#include "attributes/vec_float_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

// =====================================
// VecFloatWidget
// =====================================

class VecFloatWidget : public AbstractWidget
{
public:
  VecFloatWidget() = delete;
  VecFloatWidget(VecFloatAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false) override;

private:
  void on_sampling_change(int sampling_points_variation);
  void update_attribute_from_widget();
  void update_widget_from_attribute();

  VecFloatAttribute *p_attr;
  qsx::VectorEditor *vector_editor;
};

} // namespace attr
