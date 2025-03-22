/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QGridLayout>
#include <QLabel>

#include "attributes/widgets/range_widget.hpp"

namespace attr
{

RangeWidget::RangeWidget(RangeAttribute *p_attr) : p_attr(p_attr)
{
  // backup initial value for reset button
  this->value_bckp = this->p_attr->get_value();

  QGridLayout *layout = new QGridLayout(this);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 3);
  }

  // sliders

  // TODO ? unbounded range ?
  ValueSliders::BoundMode bcheck = ValueSliders::BoundMode::UPPER_LOWER;

  this->slider_min = new ValueSliders::DoubleSlider("low",
                                                    this->p_attr->get_value()[0],
                                                    this->p_attr->get_vmin(),
                                                    this->p_attr->get_vmax(),
                                                    bcheck);

  this->slider_max = new ValueSliders::DoubleSlider("high",
                                                    this->p_attr->get_value()[1],
                                                    this->p_attr->get_vmin(),
                                                    this->p_attr->get_vmax(),
                                                    bcheck);

  this->connect(this->slider_min,
                &ValueSliders::DoubleSlider::editEnded,
                this,
                &RangeWidget::update_attribute_from_widget);

  this->connect(this->slider_max,
                &ValueSliders::DoubleSlider::editEnded,
                this,
                &RangeWidget::update_attribute_from_widget);

  // make sure upper bound is always above lower bound
  this->connect(this->slider_min,
                &ValueSliders::DoubleSlider::valueUpdated,
                [this]()
                {
                  float val = std::min(this->slider_min->getVal(),
                                       this->slider_max->getVal());
                  this->slider_min->setVal(val);
                });

  this->connect(this->slider_max,
                &ValueSliders::DoubleSlider::valueUpdated,
                [this]()
                {
                  float val = std::max(this->slider_min->getVal(),
                                       this->slider_max->getVal());
                  this->slider_max->setVal(val);
                });

  layout->addWidget(this->slider_min, row++, 0, 1, 3);
  layout->addWidget(this->slider_max, row++, 0, 1, 3);

  // on/off
  this->button_active = new QPushButton("");
  this->button_active->setCheckable(true);
  this->button_active->setChecked(this->p_attr->get_is_active());
  layout->addWidget(this->button_active, row, 0);

  this->connect(this->button_active,
                &QPushButton::toggled,
                this,
                &RangeWidget::on_active_state_change);

  // center
  this->button_center = new QPushButton("Center");
  layout->addWidget(this->button_center, row, 1);
  this->connect(this->button_center,
                &QPushButton::pressed,
                this,
                &RangeWidget::on_center);

  // reset button
  this->button_reset = new QPushButton("Reset");
  layout->addWidget(this->button_reset, row, 2);
  this->connect(this->button_reset, &QPushButton::pressed, this, &RangeWidget::on_reset);

  this->setLayout(layout);

  // eventually update overall widget enabled/disabled state
  this->on_active_state_change();
}

void RangeWidget::on_active_state_change()
{
  bool is_active = this->button_active->isChecked();

  this->p_attr->set_is_active(is_active);

  std::string button_label = is_active ? "On" : "Off";

  this->slider_min->setEnabled(is_active);
  this->slider_max->setEnabled(is_active);
  this->button_active->setText(button_label.c_str());
  this->button_center->setEnabled(is_active);
  this->button_reset->setEnabled(is_active);

  this->update_attribute_from_widget();
}

void RangeWidget::on_center()
{
  float vptp = 0.5f * (this->p_attr->get_value()[1] - this->p_attr->get_value()[0]);

  this->slider_min->setVal(-(double)vptp);
  this->slider_max->setVal((double)vptp);
  this->slider_min->update();
  this->slider_max->update();

  this->update_attribute_from_widget();
}

void RangeWidget::on_reset()
{
  this->slider_min->setVal((double)this->value_bckp[0]);
  this->slider_max->setVal((double)this->value_bckp[1]);
  this->slider_min->update();
  this->slider_max->update();

  this->update_attribute_from_widget();
}

void RangeWidget::reset_value()
{
  this->p_attr->reset_to_save_state();

  this->slider_min->setVal((double)this->p_attr->get_value()[0]);
  this->slider_max->setVal((double)this->p_attr->get_value()[1]);
  this->slider_min->update();
  this->slider_max->update();

  this->button_active->setChecked(this->p_attr->get_is_active());
}

void RangeWidget::update_attribute_from_widget()
{
  float              x1 = (float)this->slider_min->getVal();
  float              x2 = (float)this->slider_max->getVal();
  std::vector<float> vec = {x1, x2};

  this->p_attr->set_value(vec);
  Q_EMIT this->value_changed();
}

} // namespace attr
