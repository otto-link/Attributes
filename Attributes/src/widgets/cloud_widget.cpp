/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <algorithm>
#include <random>

#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QTextStream>

#include "attributes/widgets/cloud_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

CloudWidget::CloudWidget(CloudAttribute *p_attr) : p_attr(p_attr)
{
  this->set_tool_tip_fct([p_attr]() { return p_attr ? p_attr->get_description() : ""; });

  QGridLayout *layout = new QGridLayout(this);
  setup_default_layout_spacing(layout);
  this->setLayout(layout);

  int row = 0;

  // canvas
  this->canvas = new qsx::CanvasPoints(this->p_attr->get_label().c_str(),
                                       0.f,
                                       1.f,
                                       0.f,
                                       1.f,
                                       "{:.2f}");

  // init canvas
  this->canvas->set_connected_points(this->p_attr->get_are_points_connected());

  if (this->p_attr->get_background_image_fct())
  {
    QImage bg_image = this->p_attr->get_background_image_fct()();
    this->canvas->set_bg_image(bg_image);
  }
  this->update_canvas_from_attribute();

  layout->addWidget(this->canvas, row++, 0, 1, 3);

  this->connect(this->canvas,
                &qsx::CanvasPoints::edit_ended,
                [this]() { this->update_attribute_from_canvas(); });

  // randomize button
  {
    QPushButton *button = new QPushButton("Randomize");
    layout->addWidget(button, row, 0);
    this->connect(button, &QPushButton::pressed, [this]() { this->randomize_points(); });
  }

  // clear button
  {
    QPushButton *button = new QPushButton("Clear");
    layout->addWidget(button, row, 1);
    this->connect(button, &QPushButton::pressed, [this]() { this->clear_points(); });
  }

  // from_csv button
  {
    QPushButton *button = new QPushButton("From CSV");
    layout->addWidget(button, row, 2);
    this->connect(button,
                  &QPushButton::pressed,
                  [this]() { this->load_points_from_csv(); });
  }
}

void CloudWidget::clear_points()
{
  this->p_attr->set_value({});
  this->update_canvas_from_attribute();
  Q_EMIT this->value_changed();
}

void CloudWidget::load_points_from_csv()
{
  QString fname = QFileDialog::getOpenFileName(this, "", "", "CSV file (*.csv)");
  if (fname.isNull() || fname.isEmpty())
    return;

  QFile file(fname);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  auto &points = *this->p_attr->get_value_ref();
  points.clear();
  points.reserve(1024); // envelop...

  QTextStream in(&file);

  while (!in.atEnd())
  {
    QString line = in.readLine().trimmed();
    if (line.isEmpty())
      continue;

    // Support both ',' and ';'
    QChar       sep = line.contains(';') ? ';' : ',';
    QStringList tokens = line.split(sep, Qt::SkipEmptyParts);

    if (tokens.size() < 3)
      continue;

    bool ok_x = false, ok_y = false, ok_z = false;

    float x = tokens[0].toFloat(&ok_x);
    float y = tokens[1].toFloat(&ok_y);
    float z = tokens[2].toFloat(&ok_z);

    if (ok_x && ok_y && ok_z)
    {
      points.emplace_back(x, y, z);
    }
    // else skip malformed line
  }

  file.close();

  this->update_canvas_from_attribute();
  Q_EMIT this->value_changed();
}

void CloudWidget::randomize_points()
{
  static std::random_device             rd;
  static std::mt19937                   rng(rd());
  std::uniform_real_distribution<float> dist(0.f, 1.f);

  std::vector<glm::vec3> &points = *this->p_attr->get_value_ref();

  for (size_t k = 0; k < points.size(); ++k)
    points[k] = glm::vec3(dist(rng), dist(rng), dist(rng));

  this->update_canvas_from_attribute();
  Q_EMIT this->value_changed();
}

void CloudWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  this->update_canvas_from_attribute();
  Q_EMIT this->value_changed();
}

void CloudWidget::update_attribute_from_canvas()
{
  std::vector<float> x = this->canvas->get_points_x();
  std::vector<float> y = this->canvas->get_points_y();
  std::vector<float> z = this->canvas->get_points_z();

  std::vector<glm::vec3> new_value;
  new_value.reserve(x.size());

  for (size_t k = 0; k < x.size(); ++k)
    new_value.push_back({x[k], y[k], z[k]});

  this->p_attr->set_value(new_value);

  Q_EMIT this->value_changed();
}

void CloudWidget::update_canvas_from_attribute()
{
  std::vector<glm::vec3> &points = *this->p_attr->get_value_ref();

  std::vector<float> x, y, v;
  x.reserve(points.size());
  y.reserve(points.size());
  v.reserve(points.size());

  for (const auto &p : points)
  {
    x.push_back(p.x);
    y.push_back(p.y);
    v.push_back(p.z);
  }

  this->canvas->set_points(x, y, v);
}

} // namespace attr
