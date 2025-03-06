/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

#include "attributes/widgets/choice_widget.hpp"

namespace attr
{

ChoiceWidget::ChoiceWidget(ChoiceAttribute *p_attr) : p_attr(p_attr)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  // add a label if the attribute has one
  if (!this->p_attr->get_label().empty())
  {
    QLabel *label = new QLabel(QString::fromStdString(this->p_attr->get_label()), this);
    layout->addWidget(label);
  }

  // create a button group to manage the radio buttons
  QButtonGroup *button_group = new QButtonGroup(this);

  // add a radio button for each choice in the list
  const std::vector<std::string> &choices = this->p_attr->get_choice_list();
  for (size_t k = 0; k < choices.size(); ++k)
  {
    QRadioButton *radio = new QRadioButton(QString::fromStdString(choices[k]), this);
    radio->setChecked(this->p_attr->get_value() == choices[k]);
    button_group->addButton(radio, static_cast<int>(k));
    layout->addWidget(radio);
  }

  // connect the button group's clicked signal to update the attribute
  connect(button_group,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
          this,
          [this, button_group](QAbstractButton *button)
          {
            int id = button_group->id(button);
            this->update_attribute_from_widget(this->p_attr->get_choice_list()[id]);
          });

  // set the layout for the widget
  this->setLayout(layout);
}

void ChoiceWidget::update_attribute_from_widget(const std::string &new_value)
{
  p_attr->set_value(new_value);
  Q_EMIT value_changed();
}

} // namespace attr
