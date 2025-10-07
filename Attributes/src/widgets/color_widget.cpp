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
  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  // main label
  layout->addWidget(new QLabel(this->p_attr->get_label().c_str()), 0, 0, 1, 2);

  // color label
  this->label = new QLabel();
  this->update_label_color();
  layout->addWidget(this->label, 1, 1, 1, 2);

  // color picking button
  QPushButton *button = new QPushButton("Pick color");
  layout->addWidget(button, 1, 0);

  this->connect(button,
                &QPushButton::released,
                this,
                &ColorWidget::on_color_pick_button_released);

  this->setLayout(layout);
}

void ColorWidget::on_color_pick_button_released()
{
  std::vector<float> c = this->p_attr->get_value();
  QColor             current_color = QColor(static_cast<uint8_t>(c[0] * 255.f),
                                static_cast<uint8_t>(c[1] * 255.f),
                                static_cast<uint8_t>(c[2] * 255.f),
                                static_cast<uint8_t>(c[3] * 255.f));

  QColor color = QColorDialog::getColor(current_color,
                                        this,
                                        "Select a color",
                                        QColorDialog::ShowAlphaChannel |
                                            QColorDialog::DontUseNativeDialog);

  if (color.isValid())
    this->update_attribute_from_widget(color);
}

void ColorWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->update_label_color();
}

void ColorWidget::update_attribute_from_widget(const QColor &color)
{
  if (!color.isValid())
    return;

  std::vector<float> rgba = {static_cast<float>(color.red()) / 255.f,
                             static_cast<float>(color.green()) / 255.f,
                             static_cast<float>(color.blue()) / 255.f,
                             static_cast<float>(color.alpha()) / 255.f};

  this->p_attr->set_value(rgba);
  this->update_label_color();
  Q_EMIT this->value_changed();
}

void ColorWidget::update_label_color()
{
  const auto &rgba = this->p_attr->get_value();
  QColor      color(static_cast<int>(rgba[0] * 255.f),
               static_cast<int>(rgba[1] * 255.f),
               static_cast<int>(rgba[2] * 255.f),
               static_cast<int>(rgba[3] * 255.f));

  std::string style_sheet = "QWidget {background-color: rgba(" +
                            std::to_string(color.red()) + ", " +
                            std::to_string(color.green()) + ", " +
                            std::to_string(color.blue()) + ", " +
                            std::to_string(color.alpha()) + ");}";

  this->label->setStyleSheet(style_sheet.c_str());
}

} // namespace attr
