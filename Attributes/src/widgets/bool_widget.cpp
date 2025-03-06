/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>

#include "attributes/widgets/bool_widget.hpp"

namespace attr
{

BoolWidget::BoolWidget(BoolAttribute *p_attr) : p_attr(p_attr)
{
  std::string button_label = p_attr->get_value() ? p_attr->get_label_checked()
                                                 : p_attr->get_label();

  if (this->p_attr->get_label_checked() == this->p_attr->get_label())
  {
    // --- basic toggle button on/off

    QPushButton *button = new QPushButton(button_label.c_str(), this);
    button->setCheckable(true);
    button->setChecked(p_attr->get_value());

    this->connect(button,
                  &QPushButton::toggled,
                  this,
                  [this](bool checked) { this->update_attribute_from_widget(checked); });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(button);
    this->setLayout(layout);
  }
  else
  {
    // --- two choices radio buttons

    QRadioButton *radio1 = new QRadioButton(this->p_attr->get_label().c_str(), this);
    QRadioButton *radio2 = new QRadioButton(this->p_attr->get_label_checked().c_str(),
                                            this);

    QButtonGroup *button_group = new QButtonGroup(this);
    button_group->addButton(radio1, 0);
    button_group->addButton(radio2, 1);

    // set the initial state of the radio buttons based on the attribute value
    radio1->setChecked(!p_attr->get_value());
    radio2->setChecked(p_attr->get_value());

    // use a lambda to connect the button group's buttonClicked signal to the update
    // method
    connect(button_group,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            [this, button_group](QAbstractButton *button)
            {
              int id = button_group->id(button);
              this->update_attribute_from_widget(id != 0);
            });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(radio1);
    layout->addWidget(radio2);
    this->setLayout(layout);
  }
}

void BoolWidget::update_attribute_from_widget(const bool new_value)
{
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
