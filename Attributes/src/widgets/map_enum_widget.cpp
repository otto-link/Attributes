/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/widgets/map_enum_widget.hpp"

namespace attr
{

MapEnumWidget::MapEnumWidget(MapEnumAttribute *p_attr) : p_attr(p_attr)
{
  QHBoxLayout *layout = new QHBoxLayout(this);

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
          &MapEnumWidget::update_attribute_from_widget);

  layout->addWidget(this->combobox);

  this->setLayout(layout);
}

void MapEnumWidget::update_attribute_from_widget()
{
  std::string current_choice = this->combobox->currentText().toStdString();

  this->p_attr->set_choice(current_choice);
  this->p_attr->set_value(p_attr->get_map().at(current_choice));
  Logger::get_logger()->trace("{}", p_attr->to_string());
  Q_EMIT this->value_changed();
}

} // namespace attr
