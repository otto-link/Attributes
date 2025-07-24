/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

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
    setup_default_layout_spacing(layout);
    layout->addWidget(this->button);
    this->setLayout(layout);
  }
  else
  {
    // --- two exclusive push buttons

    this->button_true = new QPushButton(this->p_attr->get_label_true().c_str(), this);
    this->button_false = new QPushButton(this->p_attr->get_label_false().c_str(), this);

    // make the buttons checkable
    this->button_true->setCheckable(true);
    this->button_false->setCheckable(true);

    // set the initial state of the buttons based on the attribute value
    this->button_true->setChecked(this->p_attr->get_value());
    this->button_false->setChecked(!this->p_attr->get_value());

    // connect the buttons' clicked signals to update the state
    this->connect(this->button_true,
                  &QPushButton::clicked,
                  this,
                  [this]()
                  {
                    if (this->button_true->isChecked())
                    {
                      this->button_false->setChecked(false);
                      this->update_attribute_from_widget(true);
                    }
                    else
                    {
                      // ensure at least one button is always checked
                      this->button_true->setChecked(true);
                    }
                  });

    this->connect(this->button_false,
                  &QPushButton::clicked,
                  this,
                  [this]()
                  {
                    if (this->button_false->isChecked())
                    {
                      this->button_true->setChecked(false);
                      this->update_attribute_from_widget(false);
                    }
                    else
                    {
                      this->button_false->setChecked(true);
                    }
                  });

    // Layout to arrange the buttons side by side
    QGridLayout *layout = new QGridLayout(this);
    setup_default_layout_spacing(layout);

    int row = 0;

    if (!this->p_attr->get_label().empty())
    {
      QLabel *label = new QLabel(QString::fromStdString(this->p_attr->get_label()), this);
      layout->addWidget(label, row++, 0, 1, 2);
    }

    layout->addWidget(this->button_true, row, 0);
    layout->addWidget(this->button_false, row, 1);
    this->setLayout(layout);
  }
}

void BoolWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  if (this->p_attr->get_label_true() == "")
  {
    this->button->setChecked(p_attr->get_value());
  }
  else
  {
    this->button_true->setChecked(this->p_attr->get_value());
    this->button_false->setChecked(!this->p_attr->get_value());
  }
}

void BoolWidget::update_attribute_from_widget(const bool new_value)
{
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
