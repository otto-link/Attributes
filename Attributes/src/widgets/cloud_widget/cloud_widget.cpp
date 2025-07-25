/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/cloud_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

CloudWidget::CloudWidget(CloudAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);
  this->setLayout(layout);

  int row = 0;

  // label
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 3);
  }

  // canvas
  this->canvas = new CloudCanvasWidget(this->p_attr, this);
  layout->addWidget(this->canvas, row++, 0, 1, 3);

  this->connect(this->canvas,
                &CloudCanvasWidget::value_changed,
                [this]() { Q_EMIT this->value_changed(); });

  // randomize button
  {
    QPushButton *button = new QPushButton("Randomize");
    layout->addWidget(button, row, 0);
    this->connect(button, &QPushButton::pressed, [this]() { this->canvas->randomize(); });
  }

  // clear button
  {
    QPushButton *button = new QPushButton("Clear");
    layout->addWidget(button, row, 1);
    this->connect(button, &QPushButton::pressed, [this]() { this->canvas->clear(); });
  }

  // from_csv button
  {
    QPushButton *button = new QPushButton("From CSV");
    layout->addWidget(button, row, 2);
    this->connect(button,
                  &QPushButton::pressed,
                  [this]() { this->canvas->load_from_csv(); });
  }
}

void CloudWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->canvas->update_widget_from_attribute();
  this->canvas->update();
}

} // namespace attr
