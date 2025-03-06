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

  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label);
  }

  QButtonGroup *button_group = new QButtonGroup(this);
  int           k = 0;

  for (auto &v : this->p_attr->get_choice_list())
  {
    QRadioButton *radio = new QRadioButton(v.c_str(), this);
    radio->setChecked(this->p_attr->get_value() == v);
    button_group->addButton(radio, k++);
    layout->addWidget(radio);
  }

  connect(button_group,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
          this,
          [this, button_group](QAbstractButton *button)
          {
            int id = button_group->id(button);
            this->update_attribute_from_widget(this->p_attr->get_choice_list()[id]);
          });

  this->setLayout(layout);
}

void ChoiceWidget::update_attribute_from_widget(const std::string &new_value)
{
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
