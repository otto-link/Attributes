#pragma once
#include <QComboBox>
#include <QHBoxLayout>

#include "attributes/helpers.hpp"
#include "attributes/logger.hpp"
#include "attributes/map_enum_attribute.hpp"

namespace attr
{

class MapEnumWidget : public QWidget
{
  Q_OBJECT

public:
  MapEnumWidget() = delete;

  MapEnumWidget(MapEnumAttribute *p_attr) : p_attr(p_attr)
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

Q_SIGNALS:
  void value_changed();

private:
  MapEnumAttribute *p_attr;

  QComboBox *combobox;

  void update_attribute_from_widget()
  {
    std::string current_choice = this->combobox->currentText().toStdString();

    this->p_attr->set_choice(current_choice);
    this->p_attr->set_value(p_attr->get_map().at(current_choice));
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
