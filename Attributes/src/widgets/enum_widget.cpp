/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QLabel>

#include "attributes/widgets/enum_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

EnumWidget::EnumWidget(EnumAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QHBoxLayout *layout = new QHBoxLayout(this);
  setup_default_layout_spacing(layout);

  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label);
  }

  this->combobox = new QComboBox();

  QStringList items;
  for (auto &[key, dummy] : this->p_attr->get_map())
    this->combobox->addItem(key.c_str());

  if (this->p_attr->get_map().contains(this->p_attr->get_choice()))
    this->combobox->setCurrentText(QString::fromStdString(this->p_attr->get_choice()));
  else
    this->combobox->setCurrentText(this->p_attr->get_map().begin()->first.c_str());

  connect(this->combobox,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &EnumWidget::update_attribute_from_widget);

  layout->addWidget(this->combobox);

  this->setLayout(layout);
}

void EnumWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->combobox->setCurrentText(QString::fromStdString(this->p_attr->get_choice()));
}

void EnumWidget::update_attribute_from_widget()
{
  std::string current_choice = this->combobox->currentText().toStdString();

  this->p_attr->set_choice(current_choice);
  this->p_attr->set_value(p_attr->get_map().at(current_choice));
  Q_EMIT this->value_changed();
}

} // namespace attr
