/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QHBoxLayout>

#include "attributes/widgets/int_widget.hpp"

namespace attr
{

IntWidget::IntWidget(IntAttribute *p_attr) : p_attr(p_attr)
{
  ValueSliders::BoundMode bcheck = ValueSliders::BoundMode::UPPER_LOWER;
  int                     vmin = this->p_attr->get_vmin();
  int                     vmax = this->p_attr->get_vmax();

  if (this->p_attr->get_vmin() == -INT_MAX && this->p_attr->get_vmax() == INT_MAX)
  {
    bcheck = ValueSliders::BoundMode::UNCHECKED;
    vmin = -10;
    vmax = 10;
  }
  else if (this->p_attr->get_vmax() == INT_MAX)
  {
    bcheck = ValueSliders::BoundMode::LOWER_ONLY;
    vmax = this->p_attr->get_value() + 10;
  }
  else if (this->p_attr->get_vmin() == -INT_MAX)
  {
    bcheck = ValueSliders::BoundMode::UPPER_ONLY;
    vmin = this->p_attr->get_value() - 10;
  }

  this->slider = new ValueSliders::IntSlider(this->p_attr->get_label().c_str(),
                                             this->p_attr->get_value(),
                                             vmin,
                                             vmax + 1,
                                             bcheck);

  this->connect(this->slider,
                &ValueSliders::IntSlider::editEnded,
                this,
                &IntWidget::update_attribute_from_widget);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(this->slider);
  this->setLayout(layout);

  // set width so that the text has enough room
  QFont        font;
  QFontMetrics font_metrics(font);
  QSize size = font_metrics.size(Qt::TextSingleLine, this->p_attr->get_label().c_str());
  this->setMinimumWidth(4.f * size.width());
}

void IntWidget::reset_value()
{
  this->p_attr->reset_to_save_state();
  this->slider->setVal(this->p_attr->get_value());
}

void IntWidget::update_attribute_from_widget()
{
  this->p_attr->set_value(this->slider->getVal());
  Q_EMIT this->value_changed();
}

} // namespace attr
