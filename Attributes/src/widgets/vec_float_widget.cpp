/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>
#include <QPainter>

#include "attributes/widgets/vec_float_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

VecFloatWidget::VecFloatWidget(VecFloatAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  this->curve_editor = new qsx::CurveEditor(p_attr->get_label());
  layout->addWidget(this->curve_editor, 0, 0, 1, 4);

  this->connect(this->curve_editor,
                &qsx::CurveEditor::edit_ended,
                this,
                &VecFloatWidget::update_attribute_from_widget);

  {
    QPushButton *button = new QPushButton("Reset");
    layout->addWidget(button, 1, 0);
    this->connect(button, &QPushButton::pressed, this, &VecFloatWidget::on_reset);
  }

  {
    QPushButton *button = new QPushButton("-1 point");
    layout->addWidget(button, 1, 1);
    this->connect(button,
                  &QPushButton::pressed,
                  this,
                  [this]() { this->on_sampling_change(-1); });
  }

  {
    QPushButton *button = new QPushButton("+1 point");
    layout->addWidget(button, 1, 2);
    this->connect(button,
                  &QPushButton::pressed,
                  this,
                  [this]() { this->on_sampling_change(1); });
  }

  {
    this->button_smooth = new QPushButton("Smooth");
    this->button_smooth->setCheckable(true);
    layout->addWidget(this->button_smooth, 1, 3);
    this->connect(this->button_smooth,
                  &QPushButton::pressed,
                  this,
                  &VecFloatWidget::on_smooth);
  }

  this->setLayout(layout);

  this->update_widget_from_attribute();
}

void VecFloatWidget::on_reset()
{
  this->curve_editor->clear_points();
  this->update_attribute_from_widget();
  Q_EMIT this->value_changed();
}

void VecFloatWidget::on_sampling_change(int sampling_points_variation)
{
  int new_count = this->curve_editor->get_sample_count() + sampling_points_variation;
  new_count = std::max(new_count, 2);
  this->curve_editor->set_sample_count(new_count);
  Q_EMIT this->value_changed();
}

void VecFloatWidget::on_smooth()
{
  bool state = this->curve_editor->get_smooth_interpolation();
  this->curve_editor->set_smooth_interpolation(!state);
  this->update_attribute_from_widget();
  Q_EMIT this->value_changed();
}

void VecFloatWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->update_widget_from_attribute();
}

void VecFloatWidget::update_attribute_from_widget()
{
  std::vector<float> vec = this->curve_editor->get_values();

  // normalize values to [vmin, vmax]
  float vmin = this->p_attr->get_vmin();
  float vmax = this->p_attr->get_vmax();

  for (auto &v : vec)
    v = v * (vmax - vmin) + vmin;

  this->p_attr->set_value(vec);

  Q_EMIT this->value_changed();
}

void VecFloatWidget::update_widget_from_attribute()
{
  std::vector<float> vec = this->p_attr->get_value();

  if (vec.empty())
    return;

  // normalize values to [0, 1]
  float vmin = this->p_attr->get_vmin();
  float vmax = this->p_attr->get_vmax();

  for (auto &v : vec)
    v = (v - vmin) / (vmax - vmin);

  this->curve_editor->set_values(vec);

  // smooth button
  this->button_smooth->setChecked(this->curve_editor->get_smooth_interpolation());
}

} // namespace attr
