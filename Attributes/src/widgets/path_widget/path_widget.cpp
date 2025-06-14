/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/path_widget.hpp"

namespace attr
{

PathWidget::PathWidget(PathAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);
  this->setLayout(layout);

  int row = 0;

  // label
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 3);
  }

  // canvas
  this->canvas = new PathCanvasWidget(this->p_attr, this);
  layout->addWidget(this->canvas, row++, 0, 1, 3);

  this->connect(this->canvas,
                &PathCanvasWidget::value_changed,
                [this]() { Q_EMIT this->value_changed(); });

  // close/open button
  {
    std::string label = this->p_attr->get_value_ref()->closed ? "Closed" : "Opened";

    QPushButton *button = new QPushButton(label.c_str());
    button->setCheckable(true);
    button->setChecked(this->p_attr->get_value_ref()->closed);

    layout->addWidget(button, row, 0);
    this->connect(
        button,
        &QPushButton::pressed,
        [this, button]()
        {
          this->p_attr->get_value_ref()->closed = !this->p_attr->get_value_ref()->closed;
          button->setText(this->p_attr->get_value_ref()->closed ? "Closed" : "Opened");
          Q_EMIT this->value_changed();
        });
  }

  // reverse button
  {
    QPushButton *button = new QPushButton("Reverse");
    layout->addWidget(button, row, 1);
    this->connect(button, &QPushButton::pressed, [this]() { this->canvas->reverse(); });
  }

  // reorder
  {
    QPushButton *button = new QPushButton("Reorder (NNS)");
    layout->addWidget(button, row, 2);
    this->connect(button,
                  &QPushButton::pressed,
                  [this]() { this->canvas->reorder_nns(); });
  }

  row++;

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

void PathWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->canvas->update_widget_from_attribute();
  this->canvas->update();
}

} // namespace attr
