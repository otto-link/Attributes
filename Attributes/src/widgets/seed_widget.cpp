/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/seed_widget.hpp"

namespace attr
{

SeedWidget::SeedWidget(SeedAttribute *p_attr) : p_attr(p_attr)
{
  value_bckp = this->p_attr->get_value();

  QGridLayout *layout = new QGridLayout(this);

  // slider
  this->slider = new ValueSliders::IntSlider(this->p_attr->get_label().c_str(),
                                             this->p_attr->get_value(),
                                             0,   // seed >= 0
                                             100, // unused
                                             ValueSliders::BoundMode::LOWER_ONLY);

  this->connect(this->slider,
                &ValueSliders::IntSlider::editEnded,
                this,
                &SeedWidget::update_attribute_from_widget);

  layout->addWidget(this->slider, 0, 0, 1, 4);

  // new button
  {
    QPushButton *button = new QPushButton("Random seed");
    layout->addWidget(button, 1, 0);

    connect(button,
            &QPushButton::released,
            [this]()
            {
              this->slider->setVal((uint)time(NULL));
              this->update_attribute_from_widget();
            });
  }

  // +1 button
  {
    QPushButton *button = new QPushButton("+1");
    layout->addWidget(button, 1, 1);

    connect(button,
            &QPushButton::released,
            [this]()
            {
              this->slider->setVal(this->slider->getVal() + 1);
              this->update_attribute_from_widget();
            });
  }

  // -1 button
  {
    QPushButton *button = new QPushButton("-1");
    layout->addWidget(button, 1, 2);

    connect(button,
            &QPushButton::released,
            [this]()
            {
              this->slider->setVal(std::max(0, this->slider->getVal() - 1));
              this->update_attribute_from_widget();
            });
  }

  // reset
  {
    QPushButton *button = new QPushButton("Reset");
    layout->addWidget(button, 1, 3);

    connect(button,
            &QPushButton::released,
            [this]()
            {
              this->slider->setVal((int)this->value_bckp);
              this->update_attribute_from_widget();
            });
  }

  this->setLayout(layout);
}

void SeedWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->slider->setVal((int)this->p_attr->get_value());
}

void SeedWidget::update_attribute_from_widget()
{
  this->p_attr->set_value((uint)this->slider->getVal());
  Q_EMIT this->value_changed();
}

} // namespace attr
