/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>

#include "attributes/widgets/cloud_widget.hpp"

namespace attr
{

CloudWidget::CloudWidget(CloudAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);
  this->setLayout(layout);

  int row = 0;

  // label
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0);
  }

  // canvas
  CloudCanvasWidget *canvas = new CloudCanvasWidget(p_attr, this);
  layout->addWidget(canvas, row++, 0);
}

} // namespace attr
