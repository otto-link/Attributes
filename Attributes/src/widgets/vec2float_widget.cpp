/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with * this
 * software. */
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>

#include "attributes/widgets/vec2float_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

Vec2FloatWidget::Vec2FloatWidget(Vec2FloatAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);

  // point selection
  {
    this->point2d_selector = new qsx::Point2DSelector(p_attr->get_label(),
                                                      p_attr->get_xmin(),
                                                      p_attr->get_xmax(),
                                                      p_attr->get_ymin(),
                                                      p_attr->get_ymax(),
                                                      this);
    this->point2d_selector->set_value({p_attr->get_value()[0], p_attr->get_value()[1]});

    this->connect(this->point2d_selector,
                  &qsx::Point2DSelector::edit_ended,
                  this,
                  &Vec2FloatWidget::update_attribute_from_widget);

    layout->addWidget(this->point2d_selector, 0, 0, 1, 2);
  }

  // center button
  {
    QPushButton *button = new QPushButton("Center");
    layout->addWidget(button, 1, 0);
    this->connect(button, &QPushButton::pressed, this, &Vec2FloatWidget::on_center);
  }

  // randomize button
  {
    QPushButton *button = new QPushButton("Random");
    layout->addWidget(button, 1, 1);
    this->connect(button, &QPushButton::pressed, this, &Vec2FloatWidget::on_randomize);
  }

  this->setLayout(layout);
}

void Vec2FloatWidget::on_center()
{
  float xc = 0.5f * (this->p_attr->get_xmin() + this->p_attr->get_xmax());
  float yc = 0.5f * (this->p_attr->get_ymin() + this->p_attr->get_ymax());
  this->point2d_selector->set_value({xc, yc});
  this->update_attribute_from_widget();
}

void Vec2FloatWidget::on_randomize()
{
  std::random_device                    rd;
  std::mt19937                          gen(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  float xc = dist(gen);
  float yc = dist(gen);

  xc = this->p_attr->get_xmin() +
       xc * (this->p_attr->get_xmax() - this->p_attr->get_xmin());
  yc = this->p_attr->get_ymin() +
       yc * (this->p_attr->get_ymax() - this->p_attr->get_ymin());

  this->point2d_selector->set_value({xc, yc});
  this->update_attribute_from_widget();
}

void Vec2FloatWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->point2d_selector->set_value({p_attr->get_value()[0], p_attr->get_value()[1]});
  this->point2d_selector->update();
}

void Vec2FloatWidget::update_attribute_from_widget()
{
  std::vector<float> new_value = {this->point2d_selector->get_value().first,
                                  this->point2d_selector->get_value().second};
  this->p_attr->set_value(new_value);
  Q_EMIT this->value_changed();
}

} // namespace attr
