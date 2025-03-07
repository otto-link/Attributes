/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

#include "attributes/widgets/bool_widget.hpp"

namespace attr
{

BoolWidget::BoolWidget(BoolAttribute *p_attr) : p_attr(p_attr)
{
  if (this->p_attr->get_label_true() == "")
  {
    // --- basic toggle button on/off

    QPushButton *button = new QPushButton(this->p_attr->get_label().c_str(), this);
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
    // --- two exclusive push buttons

    QPushButton *button1 = new QPushButton(this->p_attr->get_label_true().c_str(), this);
    QPushButton *button2 = new QPushButton(this->p_attr->get_label_false().c_str(), this);

    // make the buttons checkable
    button1->setCheckable(true);
    button2->setCheckable(true);

    // set the initial state of the buttons based on the attribute value
    button1->setChecked(this->p_attr->get_value());
    button2->setChecked(!this->p_attr->get_value());

    // connect the buttons' clicked signals to update the state
    this->connect(button1,
                  &QPushButton::clicked,
                  this,
                  [this, button1, button2]()
                  {
                    if (button1->isChecked())
                    {
                      button2->setChecked(false);
                      this->update_attribute_from_widget(false);
                    }
                    else
                    {
                      // ensure at least one button is always checked
                      button1->setChecked(true);
                    }
                  });

    this->connect(button2,
                  &QPushButton::clicked,
                  this,
                  [this, button1, button2]()
                  {
                    if (button2->isChecked())
                    {
                      button1->setChecked(false);
                      this->update_attribute_from_widget(true);
                    }
                    else
                    {
                      button2->setChecked(true);
                    }
                  });

    // Layout to arrange the buttons side by side
    QGridLayout *layout = new QGridLayout(this);

    int row = 0;

    if (!this->p_attr->get_label().empty())
    {
      QLabel *label = new QLabel(QString::fromStdString(this->p_attr->get_label()), this);
      layout->addWidget(label, row++, 0, 1, 2);
    }

    layout->addWidget(button1, row, 0);
    layout->addWidget(button2, row, 1);
    this->setLayout(layout);
  }
}

void BoolWidget::update_attribute_from_widget(const bool new_value)
{
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
