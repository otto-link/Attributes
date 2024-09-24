/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file int_attribute.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QHBoxLayout>

#include "intslider.hpp"

#include "attributes/helpers.hpp"
#include "attributes/int_attribute.hpp"
#include "attributes/logger.hpp"

namespace attr
{

class IntWidget : public QWidget
{
  Q_OBJECT

public:
  IntWidget() = delete;

  IntWidget(IntAttribute *p_attr) : p_attr(p_attr)
  {
    ValueSliders::BoundMode bcheck = convert_bound_check(this->p_attr->get_bound_check());

    this->slider = new ValueSliders::IntSlider(this->p_attr->get_label().c_str(),
                                               this->p_attr->get_value(),
                                               this->p_attr->get_vmin(),
                                               this->p_attr->get_vmax(),
                                               bcheck);

    this->connect(this->slider,
                  &ValueSliders::IntSlider::editEnded,
                  this,
                  &IntWidget::update_attribute_from_widget);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(this->slider);
    this->setLayout(layout);
  }

Q_SIGNALS:
  void value_changed();

private:
  IntAttribute *p_attr;

  ValueSliders::IntSlider *slider;

  void update_attribute_from_widget()
  {
    this->p_attr->set_value(this->slider->getVal());
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
