/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
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

    this->button = new QPushButton(this->p_attr->get_label().c_str(), this);
    this->button->setCheckable(true);
    this->button->setChecked(p_attr->get_value());

    this->connect(this->button,
                  &QPushButton::toggled,
                  this,
                  [this](bool checked) { this->update_attribute_from_widget(checked); });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(this->button);
    this->setLayout(layout);
  }
  else
  {
    // --- two exclusive push buttons

    this->button1 = new QPushButton(this->p_attr->get_label_true().c_str(), this);
    this->button2 = new QPushButton(this->p_attr->get_label_false().c_str(), this);

    // make the buttons checkable
    this->button1->setCheckable(true);
    this->button2->setCheckable(true);

    // set the initial state of the buttons based on the attribute value
    this->button1->setChecked(this->p_attr->get_value());
    this->button2->setChecked(!this->p_attr->get_value());

    // connect the buttons' clicked signals to update the state
    this->connect(this->button1,
                  &QPushButton::clicked,
                  this,
                  [this]()
                  {
                    if (this->button1->isChecked())
                    {
                      this->button2->setChecked(false);
                      this->update_attribute_from_widget(false);
                    }
                    else
                    {
                      // ensure at least one button is always checked
                      this->button1->setChecked(true);
                    }
                  });

    this->connect(this->button2,
                  &QPushButton::clicked,
                  this,
                  [this]()
                  {
                    if (this->button2->isChecked())
                    {
                      this->button1->setChecked(false);
                      this->update_attribute_from_widget(true);
                    }
                    else
                    {
                      this->button2->setChecked(true);
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

    layout->addWidget(this->button1, row, 0);
    layout->addWidget(this->button2, row, 1);
    this->setLayout(layout);
  }
}

void BoolWidget::reset_value()
{
  this->p_attr->reset_to_save_state();

  if (this->p_attr->get_label_true() == "")
  {
    this->button->setChecked(p_attr->get_value());
  }
  else
  {
    this->button1->setChecked(this->p_attr->get_value());
    this->button2->setChecked(!this->p_attr->get_value());
  }
}

void BoolWidget::update_attribute_from_widget(const bool new_value)
{
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
