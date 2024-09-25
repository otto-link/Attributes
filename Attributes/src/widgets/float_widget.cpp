/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QHBoxLayout>

#include "attributes/helpers.hpp"
#include "attributes/widgets/float_widget.hpp"

namespace attr
{

FloatWidget::FloatWidget(FloatAttribute *p_attr) : p_attr(p_attr)
{
  ValueSliders::BoundMode bcheck = convert_bound_check(this->p_attr->get_bound_check());

  this->slider = new ValueSliders::DoubleSlider(this->p_attr->get_label().c_str(),
                                                this->p_attr->get_value(),
                                                this->p_attr->get_vmin(),
                                                this->p_attr->get_vmax(),
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

void FloatWidget::update_attribute_from_widget()
{
  this->p_attr->set_value(this->slider->getVal());
  std::cout << this->p_attr->to_string() << "\n";
  Q_EMIT this->value_changed();
}

} // namespace attr
