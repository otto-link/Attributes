/* Copyright (c) 2025 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QLabel>
#include <QVBoxLayout>

#include "attributes/widgets/resolution_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ResolutionWidget::ResolutionWidget(ResolutionAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  // --- Create sliders for width and height ---
  this->slider_width = new qsx::SliderInt("Width",
                                          this->p_attr->get_width(),
                                          1,
                                          INT_MAX,
                                          true,
                                          this->p_attr->get_value_format());

  this->slider_height = new qsx::SliderInt("Height",
                                           this->p_attr->get_height(),
                                           1,
                                           INT_MAX,
                                           true,
                                           this->p_attr->get_value_format());

  // --- Connections ---
  this->connect(this->slider_width,
                &qsx::SliderInt::edit_ended,
                this,
                &ResolutionWidget::update_attribute_from_widget);

  this->connect(this->slider_height,
                &qsx::SliderInt::edit_ended,
                this,
                &ResolutionWidget::update_attribute_from_widget);

  // --- Layout setup ---
  QVBoxLayout *layout = new QVBoxLayout(this);
  setup_default_layout_spacing(layout);

  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label);
  }

  layout->addWidget(this->slider_width);
  layout->addWidget(this->slider_height);

  this->setLayout(layout);
}

void ResolutionWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->update_widget_from_attribute();
}

void ResolutionWidget::update_attribute_from_widget()
{
  // determine which slider has ignited the change signal
  bool width_has_changed = (this->p_attr->get_width() != this->slider_width->get_value());

  int w = this->slider_width->get_value();
  int h = this->slider_height->get_value();

  if (this->p_attr->get_power_of_two())
  {
    bool return_upper_w = (w >= this->p_attr->get_width());
    bool return_upper_h = (h >= this->p_attr->get_height());

    w = this->p_attr->make_power_of_two(w, return_upper_w);
    h = this->p_attr->make_power_of_two(h, return_upper_h);
  }

  if (width_has_changed)
    this->p_attr->set_width(w);
  else
    this->p_attr->set_height(h);

  this->update_widget_from_attribute();
  Q_EMIT this->value_changed();
}

void ResolutionWidget::update_widget_from_attribute()
{
  this->slider_width->set_value(this->p_attr->get_width());
  this->slider_height->set_value(this->p_attr->get_height());
}

} // namespace attr
