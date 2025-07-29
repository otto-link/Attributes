/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QFileDialog>
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

  // canvas
  this->canvas = new qsx::CanvasPoints(this->p_attr->get_label().c_str(),
                                       0.f,
                                       1.f,
                                       0.f,
                                       1.f,
                                       "{:.2f}");

  // init canvas
  if (this->p_attr->get_background_image_fct())
  {
    QImage bg_image = this->p_attr->get_background_image_fct()();
    this->canvas->set_bg_image(bg_image);
  }
  this->update_canvas_from_attribute();

  layout->addWidget(this->canvas, row++, 0, 1, 3);

  this->connect(this->canvas,
                &qsx::CanvasPoints::edit_ended,
                [this]() { this->update_attribute_from_canvas(); });

  // randomize button
  {
    QPushButton *button = new QPushButton("Randomize");
    layout->addWidget(button, row, 0);
    this->connect(button, &QPushButton::pressed, [this]() { this->randomize_points(); });
  }

  // clear button
  {
    QPushButton *button = new QPushButton("Clear");
    layout->addWidget(button, row, 1);
    this->connect(button, &QPushButton::pressed, [this]() { this->clear_points(); });
  }

  // from_csv button
  {
    QPushButton *button = new QPushButton("From CSV");
    layout->addWidget(button, row, 2);
    this->connect(button,
                  &QPushButton::pressed,
                  [this]() { this->load_points_from_csv(); });
  }
}

void CloudWidget::clear_points()
{
  std::vector<float> x, y, z;
  this->p_attr->set_value(hmap::Cloud(x, y, z));
  this->update_canvas_from_attribute();
}

void CloudWidget::load_points_from_csv()
{
  QString fname = QFileDialog::getOpenFileName(this, "", "", "CSV file (*.csv)");

  if (!fname.isNull() && !fname.isEmpty())
  {
    this->p_attr->get_value_ref()->from_csv(fname.toStdString());
    this->update_canvas_from_attribute();
  }
}

void CloudWidget::randomize_points()
{
  if (this->p_attr->get_value().get_npoints())
  {
    this->p_attr->get_value_ref()->randomize((uint)time(NULL));
    this->update_canvas_from_attribute();
  }
}

void CloudWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->update_canvas_from_attribute();
}

void CloudWidget::update_attribute_from_canvas()
{
  std::vector<float> x = this->canvas->get_points_x();
  std::vector<float> y = this->canvas->get_points_y();
  std::vector<float> z = this->canvas->get_points_z();
  this->p_attr->set_value(hmap::Cloud(x, y, z));
  Q_EMIT this->value_changed();
}

void CloudWidget::update_canvas_from_attribute()
{
  this->canvas->set_points(this->p_attr->get_value().get_x(),
                           this->p_attr->get_value().get_y(),
                           this->p_attr->get_value().get_values());
}

} // namespace attr
