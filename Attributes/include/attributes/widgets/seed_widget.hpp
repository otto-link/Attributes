#pragma once
#include <QGridLayout>
#include <QLabel>

#include "intslider.hpp"

#include "attributes/logger.hpp"
#include "attributes/seed_attribute.hpp"

namespace attr
{

class SeedWidget : public QWidget
{
  Q_OBJECT

public:
  SeedWidget() = delete;

  SeedWidget(SeedAttribute *p_attr) : p_attr(p_attr)
  {
    value_bckp = this->p_attr->get_value();

    QGridLayout *layout = new QGridLayout(this);

    // slider
    this->slider = new ValueSliders::IntSlider(this->p_attr->get_label().c_str(),
                                               this->p_attr->get_value(),
                                               0, // seed >= 0
                                               1, // unused
                                               ValueSliders::BoundMode::LOWER_ONLY);

    this->connect(this->slider,
                  &ValueSliders::IntSlider::editEnded,
                  this,
                  &SeedWidget::update_attribute_from_widget);

    layout->addWidget(this->slider, 0, 0, 1, 2);

    // new button
    {
      QPushButton *button = new QPushButton("New seed");
      layout->addWidget(button, 1, 0);

      connect(button,
              &QPushButton::released,
              [this]()
              {
                this->slider->setVal((uint)time(NULL));
                this->update_attribute_from_widget();
              });
    }

    // reset
    {
      QPushButton *button = new QPushButton("Reset");
      layout->addWidget(button, 1, 1);

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

Q_SIGNALS:
  void value_changed();

private:
  SeedAttribute *p_attr;

  uint value_bckp;

  ValueSliders::IntSlider *slider;

  void update_attribute_from_widget()
  {
    this->p_attr->set_value((uint)this->slider->getVal());
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
