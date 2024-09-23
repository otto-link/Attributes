#pragma once
#include <QHBoxLayout>

#include "doubleslider.hpp"

#include "attributes/float_attribute.hpp"
#include "attributes/helpers.hpp"
#include "attributes/logger.hpp"

namespace attr
{

class FloatWidget : public QWidget
{
  Q_OBJECT

public:
  FloatWidget() = delete;

  FloatWidget(FloatAttribute *p_attr) : p_attr(p_attr)
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
  }

Q_SIGNALS:
  void value_changed();

private:
  FloatAttribute *p_attr;

  ValueSliders::DoubleSlider *slider;

  void update_attribute_from_widget()
  {
    this->p_attr->set_value(this->slider->getVal());
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
