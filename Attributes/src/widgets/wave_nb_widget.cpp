/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QGridLayout>
#include <QLabel>

#include "attributes/widgets/wave_nb_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

WaveNbWidget::WaveNbWidget(WaveNbAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  // backup initial value for reset button
  this->value_bckp = this->p_attr->get_value();

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  // label
  int row = 0;
  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label, row, 0, 1, 2);
    row++;
  }

  // sliders
  this->slider_x = new qsx::SliderFloat("X",
                                        this->p_attr->get_value()[0],
                                        this->p_attr->get_vmin(),
                                        this->p_attr->get_vmax(),
                                        false, // +/- buttons
                                        this->p_attr->get_value_format());

  this->slider_y = new qsx::SliderFloat("Y",
                                        this->p_attr->get_value()[1],
                                        this->p_attr->get_vmin(),
                                        this->p_attr->get_vmax(),
                                        false, // +/- buttons
                                        this->p_attr->get_value_format());

  this->connect(this->slider_x,
                &qsx::SliderFloat::edit_ended,
                this,
                &WaveNbWidget::update_attribute_from_widget);

  this->connect(this->slider_y,
                &qsx::SliderFloat::edit_ended,
                this,
                &WaveNbWidget::update_attribute_from_widget);

  // copy X value to Y if the directions are linked
  this->connect(this->slider_x,
                &qsx::SliderFloat::value_changed,
                [this]()
                {
                  if (this->p_attr->get_link_xy())
                  {
                    float val = this->slider_x->get_value();
                    this->slider_y->set_value(val);
                  }
                });

  layout->addWidget(this->slider_x, row, 0);
  layout->addWidget(this->slider_y, row, 1);
  row++;

  // link / unlink
  this->button_link_xy = new QPushButton("");
  this->button_link_xy->setCheckable(true);
  this->button_link_xy->setChecked(this->p_attr->get_link_xy());
  layout->addWidget(this->button_link_xy, row, 0);

  this->connect(this->button_link_xy,
                &QPushButton::toggled,
                this,
                &WaveNbWidget::on_link_xy_state_change);

  // reset button
  this->button_reset = new QPushButton("Reset");
  layout->addWidget(this->button_reset, row, 1);
  this->connect(this->button_reset, &QPushButton::pressed, this, &WaveNbWidget::on_reset);

  this->setLayout(layout);

  // eventually update overall widget enabled/disabled state
  this->on_link_xy_state_change();

  // tool tips
  this->setToolTip(
      "This panel controls the 2D wave numbers used in the system. Adjust\n"
      "wave numbers (frequency) in X and Y directions separately, or enable\n"
      "linking to synchronize both values.");

  this->slider_x->setToolTip("Wave number (spatial frequency) in the X direction.");
  this->slider_y->setToolTip("Wave number (spatial frequency) in the Y direction.");
  this->button_link_xy->setToolTip(
      "Toggle link between X and Y wave numbers (frequency). When active, both\n"
      "directions use the same value; when inactive, you can set them separately.");

  this->button_reset->setToolTip("Reset to default settings.");
}

void WaveNbWidget::on_link_xy_state_change()
{
  bool is_linked = this->button_link_xy->isChecked();

  this->p_attr->set_link_xy(is_linked);

  std::string button_label = is_linked ? "X=Y" : "X|Y";

  if (is_linked)
    this->slider_y->set_value(this->slider_x->get_value());

  this->slider_y->setEnabled(!is_linked);
  this->button_link_xy->setText(button_label.c_str());

  this->update_attribute_from_widget();
}

void WaveNbWidget::on_reset()
{
  this->slider_x->set_value(this->value_bckp[0]);
  this->slider_y->set_value(this->value_bckp[1]);
  this->slider_x->update();
  this->slider_y->update();

  this->update_attribute_from_widget();
}

void WaveNbWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->slider_y->setEnabled(!this->p_attr->get_link_xy());

  this->slider_x->set_value(this->p_attr->get_value()[0]);
  this->slider_y->set_value(this->p_attr->get_value()[1]);
  this->slider_x->update();
  this->slider_y->update();

  // this shall be done after setting the value of the sliders because
  // of its connections (see construction)
  this->button_link_xy->setChecked(this->p_attr->get_link_xy());
}

void WaveNbWidget::update_attribute_from_widget()
{
  float              x1 = this->slider_x->get_value();
  float              x2 = this->slider_y->get_value();
  std::vector<float> vec = {x1, x2};

  this->p_attr->set_value(vec);
  Q_EMIT this->value_changed();
}

} // namespace attr
