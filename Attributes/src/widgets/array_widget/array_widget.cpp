/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/float_widget.hpp"

#include "highmap/filters.hpp"
#include "highmap/range.hpp"

#include "attributes/widgets/array_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ArrayWidget::ArrayWidget(ArrayAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  // label
  int row = 0;

  // canvas
  this->canvas = new qsx::CanvasField(this->p_attr->get_label().c_str(),
                                      DEFAULT_CANVAS_RESOLUTION,
                                      DEFAULT_CANVAS_RESOLUTION);
  this->array_data_to_widget_field_data();

  this->connect(this->canvas,
                &qsx::CanvasField::edit_ended,
                this,
                &ArrayWidget::on_canvas_edit_ended);

  layout->addWidget(this->canvas, row, 0);
  row++;

  this->setLayout(layout);
}

void ArrayWidget::array_data_to_widget_field_data()
{
  // set widget field data from attribute array data
  hmap::Array array = this->p_attr->get_value();
  hmap::remap(array);
  array = array.resample_to_shape_bilinear(
      hmap::Vec2<int>(this->canvas->get_field_width(), this->canvas->get_field_height()));
  this->canvas->set_field_data(array.vector);
}

void ArrayWidget::on_canvas_edit_ended()
{
  hmap::Vec2<int> shape_canvas = hmap::Vec2<int>(this->canvas->get_field_width(),
                                                 this->canvas->get_field_height());
  hmap::Array     array(shape_canvas);
  array.vector = this->canvas->get_field_data();

  *this->p_attr->get_value_ref() = array.resample_to_shape_bicubic(
      this->p_attr->get_shape());

  this->p_attr->get_value_ref()->dump();

  Q_EMIT this->value_changed();
}

void ArrayWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->array_data_to_widget_field_data();
  this->canvas->update();
}

} // namespace attr
