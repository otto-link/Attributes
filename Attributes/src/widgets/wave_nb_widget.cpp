/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QGridLayout>
#include <QLabel>

#include "attributes/widgets/wave_nb_widget.hpp"

namespace attr
{

WaveNbWidget::WaveNbWidget(WaveNbAttribute *p_attr) : p_attr(p_attr)
{
  // backup initial value for reset button
  this->value_bckp = this->p_attr->get_value();

  QGridLayout *layout = new QGridLayout(this);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 2);
  }

  // sliders

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
    vmax = this->p_attr->get_value().front() + 10.f;
  }
  else if (this->p_attr->get_vmin() == -FLT_MAX)
  {
    bcheck = ValueSliders::BoundMode::UPPER_ONLY;
    vmin = this->p_attr->get_value().front() - 10.f;
  }

  this->slider_x = new ValueSliders::DoubleSlider("X",
                                                  this->p_attr->get_value()[0],
                                                  vmin,
                                                  vmax,
                                                  bcheck);

  this->slider_y = new ValueSliders::DoubleSlider("Y",
                                                  this->p_attr->get_value()[1],
                                                  vmin,
                                                  vmax,
                                                  bcheck);

  this->connect(this->slider_x,
                &ValueSliders::DoubleSlider::editEnded,
                this,
                &WaveNbWidget::update_attribute_from_widget);

  this->connect(this->slider_y,
                &ValueSliders::DoubleSlider::editEnded,
                this,
                &WaveNbWidget::update_attribute_from_widget);

  // copy X value to Y if the directions are linked
  this->connect(this->slider_x,
                &ValueSliders::DoubleSlider::valueUpdated,
                [this]()
                {
                  if (this->p_attr->get_link_xy())
                  {
                    float val = this->slider_x->getVal();
                    this->slider_y->setVal(val);
                  }
                });

  layout->addWidget(this->slider_x, row++, 0, 1, 2);
  layout->addWidget(this->slider_y, row++, 0, 1, 2);

  // link / unlink
  this->button_link_xy = new QPushButton("");
  this->button_link_xy->setCheckable(true);
  this->button_link_xy->setChecked(this->p_attr->get_link_xy());
  layout->addWidget(this->button_link_xy, row, 0);

  this->connect(this->button_link_xy,
                &QPushButton::toggled,
                this,
                &WaveNbWidget::on_link_xy_state_change);

  // reset button
  this->button_reset = new QPushButton("Reset");
  layout->addWidget(this->button_reset, row, 1);
  this->connect(this->button_reset, &QPushButton::pressed, this, &WaveNbWidget::on_reset);

  this->setLayout(layout);

  // eventually update overall widget enabled/disabled state
  this->on_link_xy_state_change();
}

void WaveNbWidget::on_link_xy_state_change()
{
  bool is_linked = this->button_link_xy->isChecked();

  this->p_attr->set_link_xy(is_linked);

  std::string button_label = is_linked ? "Linked" : "Unlinked";

  if (is_linked)
    this->slider_y->setVal(this->slider_x->getVal());

  this->slider_y->setEnabled(!is_linked);
  this->button_link_xy->setText(button_label.c_str());

  this->update_attribute_from_widget();
}

void WaveNbWidget::on_reset()
{
  this->slider_x->setVal((double)this->value_bckp[0]);
  this->slider_y->setVal((double)this->value_bckp[1]);
  this->slider_x->update();
  this->slider_y->update();

  this->update_attribute_from_widget();
}

void WaveNbWidget::reset_value()
{
  this->p_attr->reset_to_save_state();

  Logger::log()->trace("here: {} {}",
                       this->p_attr->get_value()[0],
                       this->p_attr->get_value()[1]);

  this->slider_y->setEnabled(!this->p_attr->get_link_xy());

  this->slider_x->setVal((double)this->p_attr->get_value()[0]);
  this->slider_y->setVal((double)this->p_attr->get_value()[1]);
  this->slider_x->update();
  this->slider_y->update();

  // this shall be done after setting the value of the sliders because
  // of its connections (see construction)
  this->button_link_xy->setChecked(this->p_attr->get_link_xy());
}

void WaveNbWidget::update_attribute_from_widget()
{
  float              x1 = (float)this->slider_x->getVal();
  float              x2 = (float)this->slider_y->getVal();
  std::vector<float> vec = {x1, x2};

  this->p_attr->set_value(vec);
  Q_EMIT this->value_changed();
}

} // namespace attr
