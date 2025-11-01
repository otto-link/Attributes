/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General Public
 * License. The full license is in the file LICENSE, distributed with this software. */
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "attributes/widgets/choice_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ChoiceWidget::ChoiceWidget(ChoiceAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  setup_default_layout_spacing(main_layout);

  // Optional label
  if (!this->p_attr->get_label().empty())
  {
    QLabel *label = new QLabel(QString::fromStdString(this->p_attr->get_label()), this);
    main_layout->addWidget(label);
  }

  // Build layout according to mode
  this->mode = this->p_attr->get_use_combo_list() ? DisplayMode::COMBO
                                                  : DisplayMode::BUTTONS;

  if (this->mode == DisplayMode::COMBO)
    this->build_combo_ui(main_layout);
  else
    this->build_button_ui(main_layout);

  this->setLayout(main_layout);
}

void ChoiceWidget::build_combo_ui(QVBoxLayout *layout)
{
  this->combobox = new QComboBox(this);

  for (const auto &s : this->p_attr->get_choice_list())
    this->combobox->addItem(QString::fromStdString(s));

  this->combobox->setCurrentText(QString::fromStdString(this->p_attr->get_value()));

  this->connect(this->combobox,
                QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this]()
                {
                  std::string choice = this->combobox->currentText().toStdString();
                  this->p_attr->set_value(choice);
                  Q_EMIT this->value_changed();
                });

  layout->addWidget(this->combobox);
}

void ChoiceWidget::build_button_ui(QVBoxLayout *layout)
{
  QHBoxLayout *button_layout = new QHBoxLayout();
  this->button_group = new QButtonGroup(this);
  this->button_group->setExclusive(true);

  const auto        &choices = this->p_attr->get_choice_list();
  const std::string &current_value = this->p_attr->get_value();

  for (const auto &choice : choices)
  {
    QPushButton *btn = new QPushButton(QString::fromStdString(choice), this);
    btn->setCheckable(true);
    btn->setFlat(false);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    if (choice == current_value)
      btn->setChecked(true);

    button_layout->addWidget(btn);
    this->button_group->addButton(btn);
  }

  this->connect(this->button_group,
                QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
                [this](QAbstractButton *button)
                {
                  std::string selected = button->text().toStdString();
                  this->p_attr->set_value(selected);
                  Q_EMIT this->value_changed();
                });

  layout->addLayout(button_layout);
}

void ChoiceWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  const std::string &val = this->p_attr->get_value();

  if (this->mode == DisplayMode::COMBO && this->combobox)
  {
    this->combobox->setCurrentText(QString::fromStdString(val));
  }
  else if (this->mode == DisplayMode::BUTTONS && this->button_group)
  {
    for (auto *button : this->button_group->buttons())
      button->setChecked(button->text().toStdString() == val);
  }
}

void ChoiceWidget::update_attribute_from_widget(const std::string &new_value)
{
  this->p_attr->set_value(new_value);

  if (this->mode == DisplayMode::COMBO && this->combobox)
  {
    this->combobox->setCurrentText(QString::fromStdString(new_value));
  }
  else if (this->mode == DisplayMode::BUTTONS && this->button_group)
  {
    for (auto *button : this->button_group->buttons())
      button->setChecked(button->text().toStdString() == new_value);
  }

  Q_EMIT value_changed();
}

} // namespace attr
