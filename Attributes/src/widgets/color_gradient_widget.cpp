/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <stdexcept>

#include <QColorDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/color_gradient_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ColorGradientWidget::ColorGradientWidget(ColorGradientAttribute *p_attr) : p_attr(p_attr)
{
  this->picker = new qsx::ColorGradientPicker(this->p_attr->get_label().c_str(), this);

  this->connect(this->picker,
                &qsx::ColorGradientPicker::edit_ended,
                this,
                &ColorGradientWidget::update_attribute_from_widget);

  QHBoxLayout *layout = new QHBoxLayout(this);
  setup_default_layout_spacing(layout);
  layout->addWidget(this->picker);
  this->setLayout(layout);

  this->update_widget_from_attribute();
}

void ColorGradientWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->update_widget_from_attribute();
  Q_EMIT this->value_changed();
}

void ColorGradientWidget::update_widget_from_attribute()
{
  // stored values
  std::vector<Stop> value = this->p_attr->get_value();

  // some checking first
  if (value.empty())
    return;

  QVector<qsx::Stop> new_stops;

  for (const auto &v : value)
    new_stops.push_back(
        {v.position, QColor::fromRgbF(v.color[0], v.color[1], v.color[2], v.color[3])});

  this->picker->set_stops(new_stops);

  // also update the presets
  std::vector<qsx::Preset> presets;

  for (const auto &preset : this->p_attr->get_presets())
  {
    qsx::Preset new_preset;
    new_preset.name = preset.name.c_str();

    for (const auto &v : preset.stops)
    {
      new_preset.stops.push_back(
          {v.position, QColor::fromRgbF(v.color[0], v.color[1], v.color[2], v.color[3])});
    }

    presets.push_back(new_preset);
  }

  this->picker->set_presets(presets);
}

void ColorGradientWidget::update_attribute_from_widget()
{
  // update attribute value
  std::vector<Stop> *p_value = this->p_attr->get_value_ref();
  p_value->clear();

  QVector<qsx::Stop> stops = this->picker->get_stops();

  for (const auto &stop : stops)
  {
    Stop new_value = {(float)stop.position,
                      stop.color.redF(),
                      stop.color.greenF(),
                      stop.color.blueF(),
                      stop.color.alphaF()};
    p_value->push_back(new_value);
  }

  Q_EMIT this->value_changed();
}

} // namespace attr
