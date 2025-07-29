/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once
#include <QWidget>

#include "qsx/canvas_points.hpp"

#include "attributes/cloud_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

class CloudWidget : public AbstractWidget
{
  Q_OBJECT

public:
  CloudWidget() = delete;
  CloudWidget(CloudAttribute *p_attr);

  void reset_value(bool reset_to_initial_state = false);
  void update_attribute_from_canvas();
  void update_canvas_from_attribute();

private:
  void clear_points();
  void load_points_from_csv();
  void randomize_points();

  CloudAttribute    *p_attr;
  qsx::CanvasPoints *canvas;
};

} // namespace attr
