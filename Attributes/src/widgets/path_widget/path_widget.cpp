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
    layout->addWidget(label, row++, 0, 1, 2);
  }

  // canvas
  PathCanvasWidget *canvas = new PathCanvasWidget(this->p_attr, this);
  layout->addWidget(canvas, row++, 0, 1, 3);

  this->connect(canvas,
                &PathCanvasWidget::value_changed,
                [this]() { Q_EMIT this->value_changed(); });

  // randomize button
  {
    QPushButton *button = new QPushButton("Randomize");
    layout->addWidget(button, row, 0);
    this->connect(button, &QPushButton::pressed, [canvas]() { canvas->randomize(); });
  }

  // reorder
  {
    QPushButton *button = new QPushButton("Reorder (NNS)");
    layout->addWidget(button, row, 1);
    this->connect(button, &QPushButton::pressed, [canvas]() { canvas->reorder_nns(); });
  }

  // clear button
  {
    QPushButton *button = new QPushButton("Clear");
    layout->addWidget(button, row, 2);
    this->connect(button, &QPushButton::pressed, [canvas]() { canvas->clear(); });
  }
}

} // namespace attr
