/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QButtonGroup>
#include <QLabel>
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

  this->combobox = new QComboBox();

  QStringList items;
  for (auto &s : this->p_attr->get_choice_list())
    this->combobox->addItem(s.c_str());

  this->combobox->setCurrentText(this->p_attr->get_value().c_str());

  connect(this->combobox,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          [this]()
          {
            std::string current_choice = this->combobox->currentText().toStdString();
            this->p_attr->set_value(current_choice);
            Q_EMIT this->value_changed();
          });

  layout->addWidget(this->combobox);

  // set the layout for the widget
  this->setLayout(layout);
}

void ChoiceWidget::reset_value()
{
  this->p_attr->reset_to_save_state();
  this->combobox->setCurrentText(this->p_attr->get_value().c_str());
}

void ChoiceWidget::update_attribute_from_widget(const std::string &new_value)
{
  p_attr->set_value(new_value);
  Q_EMIT value_changed();
}

} // namespace attr
