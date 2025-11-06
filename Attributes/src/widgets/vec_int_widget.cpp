/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/vec_int_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

VecIntWidget::VecIntWidget(VecIntAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  std::vector<float> dummy;
  this->vector_editor = new qsx::VectorEditor(p_attr->get_label(), dummy, this);
  layout->addWidget(this->vector_editor, 0, 0, 1, 2);

  this->connect(this->vector_editor,
                &qsx::VectorEditor::edit_ended,
                this,
                &VecIntWidget::update_attribute_from_widget);

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

  this->setLayout(layout);
}

void VecIntWidget::on_sampling_change(int sampling_points_variation)
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

  this->vector_editor->set_values(vec);
}

void VecIntWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->update_widget_from_attribute();
}

void VecIntWidget::update_attribute_from_widget()
{
  std::vector<float> vec = this->vector_editor->get_values();
  std::vector<int>   vec_i = {};

  // normalize values to [vmin, vmax]
  int vmin = this->p_attr->get_vmin();
  int vmax = this->p_attr->get_vmax();

  for (auto &v : vec)
    vec_i.push_back(int(v * (vmax - vmin) + vmin));

  this->p_attr->set_value(vec_i);

  Q_EMIT this->value_changed();
}

void VecIntWidget::update_widget_from_attribute()
{
  std::vector<float> vec = {};
  std::vector<int>   vec_i = this->p_attr->get_value();

  // make sure there is at least 2 values
  if (vec.empty())
    vec = {0, 0};
  else if (vec.size() == 1)
    vec.push_back(vec.back());

  // normalize values to [0, 1]
  int vmin = this->p_attr->get_vmin();
  int vmax = this->p_attr->get_vmax();

  for (auto &v : vec_i)
    vec.push_back(float(v - vmin) / float(vmax - vmin));

  this->vector_editor->set_values(vec);
}

} // namespace attr
