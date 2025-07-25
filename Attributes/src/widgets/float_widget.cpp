/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QHBoxLayout>

#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

FloatWidget::FloatWidget(FloatAttribute *p_attr) : p_attr(p_attr)
{
  this->slider = new qsx::SliderFloat(this->p_attr->get_label().c_str(),
                                      this->p_attr->get_value(),
                                      this->p_attr->get_vmin(),
                                      this->p_attr->get_vmax(),
                                      false, // +/- buttons
                                      this->p_attr->get_value_format());

  this->connect(this->slider,
                &qsx::SliderFloat::edit_ended,
                this,
                &FloatWidget::update_attribute_from_widget);

  QHBoxLayout *layout = new QHBoxLayout(this);
  setup_default_layout_spacing(layout);
  layout->addWidget(this->slider);
  this->setLayout(layout);
}

void FloatWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->slider->set_value(this->p_attr->get_value());
}

void FloatWidget::update_attribute_from_widget()
{
  this->p_attr->set_value(this->slider->get_value());
  Q_EMIT this->value_changed();
}

} // namespace attr
