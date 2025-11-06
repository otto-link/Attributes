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

  this->vector_editor = new qsx::VectorEditor(p_attr->get_label(),
                                              this->p_attr->get_value(),
                                              this);
  layout->addWidget(this->vector_editor, 0, 0, 1, 2);

  this->connect(this->vector_editor,
                &qsx::VectorEditor::edit_ended,
                this,
                &VecFloatWidget::update_attribute_from_widget);

  {
    QPushButton *button = new QPushButton("-1 point");
    layout->addWidget(button, 1, 0);
    this->connect(button,
                  &QPushButton::pressed,
                  this,
                  [this]() { this->on_sampling_change(-1); });
  }

  {
    QPushButton *button = new QPushButton("+1 point");
    layout->addWidget(button, 1, 1);
    this->connect(button,
                  &QPushButton::pressed,
                  this,
                  [this]() { this->on_sampling_change(1); });
  }

  this->setLayout(layout);

  this->update_widget_from_attribute();
}

void VecFloatWidget::on_sampling_change(int sampling_points_variation)
{
  std::vector<float> vec = this->vector_editor->get_values();

  if (sampling_points_variation > 0)
  {
    float new_val = vec.empty() ? 0.f : vec.back();
    vec.push_back(new_val);
  }
  else
  {
    if (vec.size() > 2)
      vec.pop_back();
  }

  // int new_count = this->vector_editor->get_sample_count() + sampling_points_variation;
  // new_count = std::max(new_count, 2);
  this->vector_editor->set_values(vec);
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
  std::vector<float> vec = this->vector_editor->get_values();

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

  // make sure there is at least 2 values
  if (vec.empty())
    vec = {0.f, 0.f};
  else if (vec.size() == 1)
    vec.push_back(vec.back());

  // normalize values to [0, 1]
  float vmin = this->p_attr->get_vmin();
  float vmax = this->p_attr->get_vmax();

  for (auto &v : vec)
    v = (v - vmin) / (vmax - vmin);

  this->vector_editor->set_values(vec);
}

} // namespace attr
