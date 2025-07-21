/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QHBoxLayout>

#include "attributes/widgets/seed_widget.hpp"

namespace attr
{

SeedWidget::SeedWidget(SeedAttribute *p_attr) : p_attr(p_attr)
{
  this->slider = new qsx::SliderInt(this->p_attr->get_label().c_str(),
                                    this->p_attr->get_value(),
                                    0,
                                    INT_MAX);

  this->connect(this->slider,
                &qsx::SliderInt::value_has_changed,
                this,
                &SeedWidget::update_attribute_from_widget);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(this->slider);
  this->setLayout(layout);

  // tool tips
  this->setToolTip("Set the random seed value for reproducible results. Adjust manually\n"
                   "or generate a new random seed.");
}

void SeedWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->slider->set_value((int)this->p_attr->get_value());
}

void SeedWidget::update_attribute_from_widget()
{
  this->p_attr->set_value((uint)this->slider->get_value());
  Q_EMIT this->value_changed();
}

} // namespace attr
