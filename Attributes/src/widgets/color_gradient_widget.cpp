/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <fstream>
#include <iomanip>
#include <stdexcept>

#include <QColorDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "attributes/widgets/color_gradient_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

ColorGradientWidget::ColorGradientWidget(ColorGradientAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  this->picker = new qsx::ColorGradientPicker(this->p_attr->get_label().c_str(), this);

  this->connect(this->picker,
                &qsx::ColorGradientPicker::edit_ended,
                this,
                &ColorGradientWidget::update_attribute_from_widget);

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);
  this->setLayout(layout);

  layout->addWidget(this->picker, 0, 0, 1, 2);

  // export / import buttons
  {
    QPushButton *button = new QPushButton("Export");
    layout->addWidget(button, 1, 0);

    this->connect(button, &QPushButton::released, this, &ColorGradientWidget::on_export);
  }

  {
    QPushButton *button = new QPushButton("Import");
    layout->addWidget(button, 1, 1);

    this->connect(button, &QPushButton::released, this, &ColorGradientWidget::on_import);
  }

  this->update_widget_from_attribute();
}

void ColorGradientWidget::on_export()
{
  Logger::log()->trace("ColorGradientWidget::on_export");

  QString fname = QFileDialog::getSaveFileName(this,
                                               "Save as...",
                                               "",
                                               "JSON files (*.json)");

  if (fname.isNull() || fname.isEmpty())
    return;

  nlohmann::json json = this->p_attr->json_to();

  std::ofstream outfile(fname.toStdString());
  if (outfile.is_open())
  {
    outfile << json.dump(4);
    outfile.close();
    Logger::log()->trace("json_to_file: JSON successfully written to {}",
                         fname.toStdString());
  }
  else
  {
    Logger::log()->error("json_to_file: Could not open file {} to save JSON",
                         fname.toStdString());
  }
}

void ColorGradientWidget::on_import()
{
  Logger::log()->trace("ColorGradientWidget::on_import");

  QString fname = QFileDialog::getOpenFileName(this,
                                               "Load...",
                                               "",
                                               "JSON files (*.json)");

  if (fname.isNull() || fname.isEmpty())
    return;

  nlohmann::json json;
  std::ifstream  file(fname.toStdString());

  if (file.is_open())
  {
    file >> json;
    file.close();
    Logger::log()->trace("json_from_file: JSON successfully loaded from {}",
                         fname.toStdString());

    this->p_attr->json_from(json);
    this->update_widget_from_attribute();
    Q_EMIT this->value_changed();
  }
  else
  {
    Logger::log()->error("json_from_file: Could not open file {} to load JSON",
                         fname.toStdString());
  }
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
