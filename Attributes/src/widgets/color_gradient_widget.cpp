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
                              (float)qcolor.redF(),
                              (float)qcolor.greenF(),
                              (float)qcolor.blueF(),
                              (float)qcolor.alphaF()};

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
  QColorDialog color_dialog;
  color_dialog.setOption(QColorDialog::ShowAlphaChannel, true);
  QColor qcolor = color_dialog.getColor();

  if (qcolor.isValid())
  {
    std::vector<float> color = {0.f,
                                (float)qcolor.redF(),
                                (float)qcolor.greenF(),
                                (float)qcolor.blueF(),
                                (float)qcolor.alphaF()};

    // retrieve corresponding widget
    ColorbarWidget *colorbar_item = dynamic_cast<ColorbarWidget *>(
        this->color_list->itemWidget(item));

    float pos = colorbar_item->get_colors().front()[0];

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

void ColorGradientWidget::reset_value()
{
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

      std::vector<float> color = colorbar_item->get_colors().front();
      this->p_attr->get_value_ref()->push_back(color);
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
