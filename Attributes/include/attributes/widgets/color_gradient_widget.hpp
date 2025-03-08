/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_gradient_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QListWidget>

#include "attributes/color_gradient_attribute.hpp"
#include "attributes/widgets/abstract_widget.hpp"
#include "attributes/widgets/colorbar_widget.hpp"

namespace attr
{

class ColorGradientWidget : public AbstractWidget
{
public:
  ColorGradientWidget() = delete;

  ColorGradientWidget(ColorGradientAttribute *p_attr);

  void reset_value() override;

public Q_SLOTS:
  void add_color();

  void on_item_double_click(QListWidgetItem *item);

  void remove_color();

private:
  ColorGradientAttribute *p_attr;

  ColorbarWidget *colorbar;

  QListWidget *color_list;

  void update();

  void update_attribute();

  void update_color_list();

  void update_label_gradient();
};

} // namespace attr
