/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QHBoxLayout>

#include "attributes/widgets/float_widget.hpp"

namespace attr
{

FloatWidget::FloatWidget(FloatAttribute *p_attr) : p_attr(p_attr)
{
  ValueSliders::BoundMode bcheck = ValueSliders::BoundMode::UPPER_LOWER;
  float                   vmin = this->p_attr->get_vmin();
  float                   vmax = this->p_attr->get_vmax();

  if (this->p_attr->get_vmin() == -FLT_MAX && this->p_attr->get_vmax() == FLT_MAX)
  {
    bcheck = ValueSliders::BoundMode::UNCHECKED;
    vmin = -10;
    vmax = 10;
  }
  else if (this->p_attr->get_vmax() == FLT_MAX)
  {
    bcheck = ValueSliders::BoundMode::LOWER_ONLY;
    vmax = this->p_attr->get_value() + 10.f;
  }
  else if (this->p_attr->get_vmin() == -FLT_MAX)
  {
    bcheck = ValueSliders::BoundMode::UPPER_ONLY;
    vmin = this->p_attr->get_value() - 10.f;
  }

  this->slider = new ValueSliders::DoubleSlider(this->p_attr->get_label().c_str(),
                                                this->p_attr->get_value(),
                                                vmin,
                                                vmax,
                                                bcheck);

  this->connect(this->slider,
                &ValueSliders::DoubleSlider::editEnded,
                this,
                &FloatWidget::update_attribute_from_widget);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(this->slider);
  this->setLayout(layout);

  // set width so that the text has enough room
  QFont        font;
  QFontMetrics font_metrics(font);
  QSize size = font_metrics.size(Qt::TextSingleLine, this->p_attr->get_label().c_str());
  this->setMinimumWidth(4.f * size.width());
}

void FloatWidget::reset_value()
{
  this->p_attr->reset_to_save_state();
  this->slider->setVal(this->p_attr->get_value());
}

void FloatWidget::update_attribute_from_widget()
{
  this->p_attr->set_value(this->slider->getVal());
  Q_EMIT this->value_changed();
}

} // namespace attr
