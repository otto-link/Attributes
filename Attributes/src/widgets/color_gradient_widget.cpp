/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QColorDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/color_gradient_widget.hpp"

namespace attr
{

ColorGradientWidget::ColorGradientWidget(ColorGradientAttribute *p_attr) : p_attr(p_attr)
{
  QGridLayout *layout = new QGridLayout(this);

  int row = 0;

  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row++, 0, 1, 2);
  }

  this->colorbar = new ColorbarWidget(this);
  this->colorbar->update_colors(p_attr->get_value());
  layout->addWidget(this->colorbar, row, 0, 1, 2);
  row++;

  QPushButton *add_button = new QPushButton("Add color", this);
  QPushButton *remove_button = new QPushButton("Remove selected", this);

  this->connect(add_button, &QPushButton::clicked, this, &ColorGradientWidget::add_color);
  this->connect(remove_button,
                &QPushButton::clicked,
                this,
                &ColorGradientWidget::remove_color);

  layout->addWidget(add_button, row, 0);
  layout->addWidget(remove_button, row, 1);
  row++;

  this->color_list = new QListWidget(this);
  this->update_color_list();

  this->connect(this->color_list,
                &QListWidget::itemDoubleClicked,
                this,
                &ColorGradientWidget::on_item_double_click);

  layout->addWidget(this->color_list, row, 0, 1, 2);

  this->setLayout(layout);
}

void ColorGradientWidget::add_color()
{
  QColorDialog color_dialog;
  color_dialog.setOption(QColorDialog::ShowAlphaChannel, true);
  QColor qcolor = color_dialog.getColor();

  std::vector<float> color = {1.f,
                              qcolor.redF(),
                              qcolor.greenF(),
                              qcolor.blueF(),
                              qcolor.alphaF()};

  // insert new color next to the currently selected color (if any),
  // else put it at the end
  QListWidgetItem *selectedItem = this->color_list->currentItem();

  int ncolors = this->p_attr->get_value().size();
  int selected_row = ncolors - 1;

  if (selectedItem)
    selected_row = this->color_list->row(selectedItem);

  this->p_attr->get_value_ref()->insert(this->p_attr->get_value_ref()->begin() +
                                            selected_row + 1,
                                        color);

  // redefine color positions in [0, 1]
  int new_ncolors = this->p_attr->get_value().size();

  for (size_t k = 0; k < (size_t)new_ncolors; k++)
    this->p_attr->get_value_ref()->at(k)[0] = (float)k / (new_ncolors - 1);

  // update colorbar
  this->colorbar->update_colors(this->p_attr->get_value());
  this->update_color_list();

  Q_EMIT this->value_changed();
}

void ColorGradientWidget::on_item_double_click(QListWidgetItem *item)
{
  // get current color from corresponding widget event
  ColorbarWidget *colorbar_item = dynamic_cast<ColorbarWidget *>(
      this->color_list->itemWidget(item));

  std::vector<float> color_info = {0.f, 0.f, 0.f, 0.f};
  if (!colorbar_item->get_colors().empty())
    color_info = colorbar_item->get_colors().front();

  float pos = color_info[0];

  QColor current_color = QColor(static_cast<uint8_t>(color_info[1] * 255.f),
                                static_cast<uint8_t>(color_info[2] * 255.f),
                                static_cast<uint8_t>(color_info[3] * 255.f),
                                static_cast<uint8_t>(color_info[4] * 255.f));

  QColorDialog color_dialog;
  color_dialog.setOption(QColorDialog::ShowAlphaChannel, true);
  QColor qcolor = color_dialog.getColor(current_color, this, "Select a color");

  if (qcolor.isValid())
  {
    std::vector<float> color = {0.f,
                                qcolor.redF(),
                                qcolor.greenF(),
                                qcolor.blueF(),
                                qcolor.alphaF()};

    colorbar_item->update_colors({{pos, color[1], color[2], color[3], color[4]}});
    this->update();
  }
}

void ColorGradientWidget::remove_color()
{
  // do not allow "zero" colors, at least one color needed
  if (this->color_list->count() > 1)
  {
    QListWidgetItem *selected_item = this->color_list->currentItem();
    delete selected_item;
    this->update();
  }
}

void ColorGradientWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();
  this->colorbar->update_colors(this->p_attr->get_value());
  this->update_color_list();
}

void ColorGradientWidget::update()
{
  this->update_attribute();
  this->colorbar->update_colors(this->p_attr->get_value());
  this->update_color_list();

  Q_EMIT this->value_changed();
}

void ColorGradientWidget::update_attribute()
{
  // update attribute value
  this->p_attr->get_value_ref()->clear();

  for (int i = 0; i < this->color_list->count(); ++i)
  {
    QListWidgetItem *item = this->color_list->item(i);
    if (item)
    {
      // retrieve corresponding widget
      ColorbarWidget *colorbar_item = dynamic_cast<ColorbarWidget *>(
          this->color_list->itemWidget(item));

      if (colorbar_item)
        if (!colorbar_item->get_colors().empty())
        {
          std::vector<float> color = colorbar_item->get_colors().front();
          this->p_attr->get_value_ref()->push_back(color);
        }
    }
  }
}

void ColorGradientWidget::update_color_list()
{
  this->color_list->clear();

  for (auto &c : this->p_attr->get_value())
  {
    QListWidgetItem *item = new QListWidgetItem(this->color_list);
    ColorbarWidget  *cbar = new ColorbarWidget({c});
    this->color_list->setItemWidget(item, cbar);
  }
}

} // namespace attr
