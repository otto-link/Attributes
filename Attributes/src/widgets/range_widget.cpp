/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QHBoxLayout>
#include <QLabel>

#include "attributes/widgets/range_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

RangeWidget::RangeWidget(RangeAttribute *p_attr) : p_attr(p_attr)
{
  // backup initial value for reset button
  this->value_bckp = this->p_attr->get_value();

  QHBoxLayout *layout = new QHBoxLayout(this);
  setup_default_layout_spacing(layout);

  this->slider = new qsx::SliderRange(this->p_attr->get_label().c_str(),
                                      this->p_attr->get_value()[0],
                                      this->p_attr->get_value()[1],
                                      this->p_attr->get_vmin(),
                                      this->p_attr->get_vmax(),
                                      this->p_attr->get_value_format());

  this->slider->set_histogram_fct(this->p_attr->get_histogram_fct());
  this->slider->set_autorange(this->p_attr->get_autorange());

  this->connect(this->slider,
                &qsx::SliderRange::value_has_changed,
                this,
                &RangeWidget::update_attribute_from_widget);

  this->connect(this,
                &RangeWidget::update_bins,
                this->slider,
                &qsx::SliderRange::on_update_bins);

  // eventually update overall widget enabled/disabled state
  layout->addWidget(this->slider);
  this->setLayout(layout);
}

void RangeWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->slider->set_value(0, this->p_attr->get_value()[0]);
  this->slider->set_value(1, this->p_attr->get_value()[1]);
  this->slider->set_is_enabled(this->p_attr->get_is_active());
}

void RangeWidget::update_attribute_from_widget()
{
  float              x1 = this->slider->get_value(0);
  float              x2 = this->slider->get_value(1);
  std::vector<float> vec = {x1, x2};

  this->p_attr->set_value(vec);
  this->p_attr->set_is_active(this->slider->get_is_enabled());
  Q_EMIT this->value_changed();
}

} // namespace attr
