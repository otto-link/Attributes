/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QLabel>
#include <QVBoxLayout>

#include "attributes/widgets/string_widget.hpp"

namespace attr
{

StringWidget::StringWidget(StringAttribute *p_attr) : p_attr(p_attr)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  if (!this->p_attr->get_label().empty())
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label);
  }

  this->line_edit = new QLineEdit;
  this->line_edit->setText(this->p_attr->get_value().c_str());
  this->line_edit->setReadOnly(this->p_attr->get_read_only());
  layout->addWidget(this->line_edit);

  this->connect(this->line_edit,
                &QLineEdit::textChanged,
                [this](const QString &text)
                {
                  this->p_attr->set_value(text.toStdString());
                  Q_EMIT this->value_changed();
                });

  this->setLayout(layout);
}

} // namespace attr
