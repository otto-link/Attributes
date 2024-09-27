/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "doubleslider.hpp"

#include "highmap/filters.hpp"
#include "highmap/range.hpp"

#include "attributes/widgets/array_widget.hpp"

namespace attr
{

ArrayWidget::ArrayWidget(ArrayAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0);
  }

  // canvas
  this->canvas = new CanvasWidget();
  this->canvas->set_image(this->array_to_image());

  this->connect(this->canvas,
                &CanvasWidget::edit_ended,
                this,
                &ArrayWidget::on_canvas_edit_ended);

  layout->addWidget(this->canvas, row++, 0, 1, 4);

  // brush type
  QComboBox *combo = new QComboBox();

  QStringList items;
  for (auto &[key, _] : brush_kernel_map)
    combo->addItem(key.c_str());

  combo->setCurrentText("Cubic pulse");

  connect(combo,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          [this, combo]()
          {
            std::string choice = combo->currentText().toStdString();
            this->canvas->set_kernel_type(brush_kernel_map.at(choice));
          });

  layout->addWidget(combo, row, 0);

  // brush intensity
  ValueSliders::DoubleSlider *slider = new ValueSliders::DoubleSlider(
      "Intensity",
      this->canvas->get_brush_intensity(),
      0.f,
      1.f,
      ValueSliders::BoundMode::UPPER_LOWER);

  this->connect(slider,
                &ValueSliders::DoubleSlider::editEnded,
                [this, slider]()
                { this->canvas->set_brush_intensity(slider->getVal()); });

  layout->addWidget(slider, row, 1);

  // smooth button
  QPushButton *smooth_button = new QPushButton("Smooth");
  this->connect(smooth_button, &QPushButton::pressed, [this]() { this->smooth_array(); });
  layout->addWidget(smooth_button, row, 2);

  // clear button
  QPushButton *clear_button = new QPushButton("Clear");
  this->connect(clear_button,
                &QPushButton::pressed,
                [this]()
                {
                  this->canvas->clear();
                  Q_EMIT this->value_changed();
                });
  layout->addWidget(clear_button, row, 3);

  this->setLayout(layout);
}

QImage ArrayWidget::array_to_image()
{
  QImage image = QImage(this->p_attr->get_shape().x,
                        this->p_attr->get_shape().y,
                        QImage::Format_RGB32);

  hmap::Array *p_array = this->p_attr->get_value_ref();

  hmap::Array array_remap = *p_array;
  hmap::remap(array_remap, 0.f, 255.f);

  for (int i = 0; i < p_array->shape.x; i++)
    for (int j = 0; j < p_array->shape.y; j++)
    {
      int value = (int)array_remap(i, p_array->shape.y - 1 - j);
      image.setPixelColor(i, j, QColor(value, value, value));
    }

  return image;
}

void ArrayWidget::on_canvas_edit_ended(QImage *p_image)
{
  // use Qt to interpolate image to the array size
  QSize  size = QSize(this->p_attr->get_shape().x, this->p_attr->get_shape().y);
  QImage scaled_image = p_image->scaled(size);

  // transfer image values to the array
  hmap::Array *p_array = this->p_attr->get_value_ref();

  for (int i = 0; i < p_array->shape.x; i++)
    for (int j = 0; j < p_array->shape.y; j++)
      (*p_array)(i, j) = (float)qGray(scaled_image.pixel(i, p_array->shape.y - 1 - j)) /
                         255.f;

  Q_EMIT this->value_changed();
}

void ArrayWidget::smooth_array()
{
  hmap::Array *p_array = this->p_attr->get_value_ref();

  float radius = 0.02f;
  int   ir = std::max((int)(radius * p_array->shape.x), 1);
  hmap::smooth_cpulse(*p_array, ir);

  QImage smoothed_image = this->array_to_image();
  this->canvas->set_image(smoothed_image);
  this->canvas->update();

  Q_EMIT this->value_changed();
}

} // namespace attr
