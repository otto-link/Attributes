/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QHBoxLayout>

#include "attributes/widgets/bool_widget.hpp"

namespace attr
{

BoolWidget::BoolWidget(BoolAttribute *p_attr) : p_attr(p_attr)
{
  std::string button_label = this->p_attr->get_value() ? this->p_attr->get_label_checked()
                                                       : this->p_attr->get_label();
  this->button = new QPushButton(button_label.c_str());

  this->button->setCheckable(true);
  this->button->setChecked(this->p_attr->get_value());

  this->connect(this->button,
                &QPushButton::toggled,
                [this]()
                {
                  this->update_attribute_from_widget();

                  // update label according to value
                  if (this->p_attr->get_value())
                    this->button->setText(this->p_attr->get_label_checked().c_str());
                  else
                    this->button->setText(this->p_attr->get_label().c_str());
                });

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(this->button);
  this->setLayout(layout);
}

void BoolWidget::update_attribute_from_widget()
{
  this->p_attr->set_value(this->button->isChecked());
  Q_EMIT this->value_changed();
}

} // namespace attr
