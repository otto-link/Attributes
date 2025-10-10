/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>

#include "attributes/widgets/color_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ColorWidget::ColorWidget(ColorAttribute *p_attr) : p_attr(p_attr)
{
  this->picker = new qsx::ColorPicker(this->p_attr->get_label().c_str(), this);

  this->connect(this->picker,
                &qsx::ColorPicker::edit_ended,
                this,
                &ColorWidget::update_attribute_from_widget);

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);
  this->setLayout(layout);

  layout->addWidget(this->picker, 0, 0);

  this->update_widget_from_attribute();
}

// void ColorWidget::on_color_pick_button_released()
// {
//   std::vector<float> c = this->p_attr->get_value();
//   QColor             current_color = QColor(static_cast<uint8_t>(c[0] * 255.f),
//                                 static_cast<uint8_t>(c[1] * 255.f),
//                                 static_cast<uint8_t>(c[2] * 255.f),
//                                 static_cast<uint8_t>(c[3] * 255.f));

//   QColor color = QColorDialog::getColor(current_color,
//                                         this,
//                                         "Select a color",
//                                         QColorDialog::ShowAlphaChannel |
//                                             QColorDialog::DontUseNativeDialog);

//   if (color.isValid())
//     this->update_attribute_from_widget(color);
// }

void ColorWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->update_widget_from_attribute();
}

void ColorWidget::update_attribute_from_widget()
{
  QColor color = this->picker->get_color();

  std::vector<float> rgba = {static_cast<float>(color.red()) / 255.f,
                             static_cast<float>(color.green()) / 255.f,
                             static_cast<float>(color.blue()) / 255.f,
                             static_cast<float>(color.alpha()) / 255.f};

  this->p_attr->set_value(rgba);
  Q_EMIT this->value_changed();
}

void ColorWidget::update_widget_from_attribute()
{
  const auto &rgba = this->p_attr->get_value();
  QColor      color(static_cast<int>(rgba[0] * 255.f),
               static_cast<int>(rgba[1] * 255.f),
               static_cast<int>(rgba[2] * 255.f),
               static_cast<int>(rgba[3] * 255.f));

  this->picker->set_color(color);
}

} // namespace attr
