/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <fstream>

#include <QFileDialog>
#include <QFont>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "attributes/widgets/attributes_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

#include "attributes/widgets/array_widget.hpp"
#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/choice_widget.hpp"
#include "attributes/widgets/cloud_widget.hpp"
#include "attributes/widgets/color_gradient_widget.hpp"
#include "attributes/widgets/color_widget.hpp"
#include "attributes/widgets/enum_widget.hpp"
#include "attributes/widgets/filename_widget.hpp"
#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/int_widget.hpp"
#include "attributes/widgets/path_widget.hpp"
#include "attributes/widgets/range_widget.hpp"
#include "attributes/widgets/seed_widget.hpp"
#include "attributes/widgets/string_widget.hpp"
#include "attributes/widgets/vec2float_widget.hpp"
#include "attributes/widgets/vec_float_widget.hpp"
#include "attributes/widgets/vec_int_widget.hpp"
#include "attributes/widgets/wave_nb_widget.hpp"

// Helper macro to simplify widget creation
#define RETURN_IF_MATCH(attr_type, widget_class, attribute_class, p_attr)                \
  if ((p_attr)->get_type() == AttributeType::attr_type)                                  \
    return new widget_class(dynamic_cast<attribute_class *>((p_attr)));

namespace attr
{

AbstractWidget *get_attribute_widget(AbstractAttribute *p_attr)
{
  RETURN_IF_MATCH(BOOL, BoolWidget, BoolAttribute, p_attr);
  RETURN_IF_MATCH(CHOICE, ChoiceWidget, ChoiceAttribute, p_attr);
  RETURN_IF_MATCH(COLOR, ColorWidget, ColorAttribute, p_attr);
  RETURN_IF_MATCH(COLOR_GRADIENT, ColorGradientWidget, ColorGradientAttribute, p_attr);
  RETURN_IF_MATCH(FILENAME, FilenameWidget, FilenameAttribute, p_attr);
  RETURN_IF_MATCH(FLOAT, FloatWidget, FloatAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_ARRAY, ArrayWidget, ArrayAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_CLOUD, CloudWidget, CloudAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_PATH, PathWidget, PathAttribute, p_attr);
  RETURN_IF_MATCH(INT, IntWidget, IntAttribute, p_attr);
  RETURN_IF_MATCH(ENUM, EnumWidget, EnumAttribute, p_attr);
  RETURN_IF_MATCH(RANGE, RangeWidget, RangeAttribute, p_attr);
  RETURN_IF_MATCH(SEED, SeedWidget, SeedAttribute, p_attr);
  RETURN_IF_MATCH(STRING, StringWidget, StringAttribute, p_attr);
  RETURN_IF_MATCH(VEC_FLOAT, VecFloatWidget, VecFloatAttribute, p_attr);
  RETURN_IF_MATCH(VEC_INT, VecIntWidget, VecIntAttribute, p_attr);
  RETURN_IF_MATCH(VEC2FLOAT, Vec2FloatWidget, Vec2FloatAttribute, p_attr);
  RETURN_IF_MATCH(WAVE_NB, WaveNbWidget, WaveNbAttribute, p_attr);

  Logger::log()->warn("Could not find any widget for the attribute type requested");

  return nullptr;
}

AttributesWidget::AttributesWidget(
    std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map,
    std::vector<std::string>                                  *p_attr_ordered_key,
    const std::string                                         &widget_title,
    const bool add_save_reset_state_buttons)
    : p_attr_map(p_attr_map), p_attr_ordered_key(p_attr_ordered_key)
{
  std::string title = widget_title.empty() ? "Attribute settings" : widget_title;
  this->setWindowTitle(title.c_str());

  // Define the attribute order either on the key map order or on a given order provided
  // as a key list (optional)
  std::vector<std::string> attr_key_queue = p_attr_ordered_key &&
                                                    !p_attr_ordered_key->empty()
                                                ? *p_attr_ordered_key
                                                : [&]()
  {
    std::vector<std::string> keys;
    for (const auto &[k, _] : *p_attr_map)
      keys.push_back(k);
    return keys;
  }();

  // Setup layout
  QVBoxLayout *layout = new QVBoxLayout(this);
  setup_default_layout_spacing(layout);

  // main buttons
  if (add_save_reset_state_buttons)
  {
    QPushButton *restore_button = new QPushButton("Restore save state", this);
    layout->addWidget(restore_button);

    this->connect(restore_button,
                  &QPushButton::released,
                  this,
                  &AttributesWidget::on_restore_save_state);

    QPushButton *save_state_button = new QPushButton("Save current state", this);
    layout->addWidget(save_state_button);

    this->connect(save_state_button,
                  &QPushButton::released,
                  this,
                  &AttributesWidget::on_save_state);

    QPushButton *load_button = new QPushButton("Load preset", this);
    layout->addWidget(load_button);

    this->connect(load_button,
                  &QPushButton::released,
                  this,
                  &AttributesWidget::on_load_preset);

    QPushButton *save_button = new QPushButton("Save preset", this);
    layout->addWidget(save_button);

    this->connect(save_button,
                  &QPushButton::released,
                  this,
                  &AttributesWidget::on_save_preset);

    QPushButton *reset_button = new QPushButton("Reset settings", this);
    layout->addWidget(reset_button);

    this->connect(reset_button,
                  &QPushButton::released,
                  this,
                  &AttributesWidget::on_restore_initial_state);
  }

  // To check the number of widgets corresponds to the number of keys in
  // "p_attr_ordered_key"
  int count = 0;

  for (const auto &key : attr_key_queue)
  {
    if (key == "_SEPARATOR_")
    {
      QLabel *spacer = new QLabel("");
      layout->addWidget(spacer);
    }
    else if (key.substr(0, 6) == "_TEXT_")
    {
      std::string title = key.substr(6);

      QWidget     *separator_widget = new QWidget;
      QHBoxLayout *sep_layout = new QHBoxLayout(separator_widget);
      setup_default_layout_spacing(sep_layout);

      QLabel *label = new QLabel(title.c_str());
      label->setStyleSheet("font-weight: bold;");
      sep_layout->addWidget(label);

      layout->addWidget(separator_widget);
    }
    else if (key.substr(0, 16) == "_SEPARATOR_TEXT_")
    {
      std::string title = key.substr(16);

      QWidget     *separator_widget = new QWidget;
      QHBoxLayout *sep_layout = new QHBoxLayout(separator_widget);
      setup_default_layout_spacing(sep_layout);

      QFrame *leftLine = new QFrame;
      leftLine->setFrameShape(QFrame::HLine);
      leftLine->setFrameShadow(QFrame::Sunken);

      QLabel *label = new QLabel(title.c_str());
      label->setStyleSheet("font-weight: bold;");

      QFrame *rightLine = new QFrame;
      rightLine->setFrameShape(QFrame::HLine);
      rightLine->setFrameShadow(QFrame::Sunken);

      sep_layout->addWidget(leftLine);
      sep_layout->addWidget(label);
      sep_layout->addWidget(rightLine);

      sep_layout->setStretch(0, 1);
      sep_layout->setStretch(2, 4);

      layout->addWidget(separator_widget);
    }
    else if (p_attr_map->contains(key))
    {
      AbstractAttribute *p_attr = p_attr_map->at(key).get();
      AbstractWidget    *widget = get_attribute_widget(p_attr);
      layout->addWidget(widget);

      this->connect(widget,
                    &AbstractWidget::value_changed,
                    this,
                    &AttributesWidget::value_changed);

      this->widget_map[key] = widget;

      count++;
    }
    else
    {
      Logger::log()->critical(
          "Unknown attribute key {} in AttributesWidget (check attr_ordered_key)",
          key);
    }
  }

  if (p_attr_ordered_key && count != static_cast<int>(p_attr_map->size()))
  {
    Logger::log()->critical(
        "Missing attributes in AttributesWidget (check attr_ordered_key)");
    throw std::runtime_error(
        "Missing attributes in AttributesWidget (check attr_ordered_key)");
  }

  // As a last resort, for empty "settings"
  if (p_attr_map->empty())
  {
    QLabel *widget = new QLabel("No settings", this);
    QFont   font = widget->font();
    font.setItalic(true);
    widget->setFont(font);
    layout->addWidget(widget);
  }

  this->setLayout(layout);
}

void AttributesWidget::on_load_preset()
{
  Logger::log()->trace("AttributesWidget::on_load_preset");

  QString fname = QFileDialog::getOpenFileName(nullptr,
                                               "preset.json",
                                               ".",
                                               "json file (*.json)");

  if (!fname.isNull() && !fname.isEmpty())
  {
    nlohmann::json json;
    std::ifstream  file(fname.toStdString());

    if (file.is_open())
    {
      file >> json;
      file.close();
      Logger::log()->trace("JSON successfully loaded from {}", fname.toStdString());

      for (auto &[key, pa] : *this->p_attr_map)
      {
        // do some checking before deserializing the data
        if (json.contains(key) && json[key]["type_string"] == pa->get_type_string())
        {
          // use save/restore state to update widget (quick and dirty)
          pa->json_from(json[key]);
          pa->save_state();
          this->widget_map.at(key)->reset_value();
        }
        else
          Logger::log()->error("Could not load preset for parameter: {}", key);
      }
    }
    else
      Logger::log()->error("Could not open file {} to load JSON", fname.toStdString());
  }
}

void AttributesWidget::on_restore_initial_state()
{
  Logger::log()->trace("AttributesWidget::on_restore_initial_state");

  bool reset_to_initial_state = true;

  for (auto &[k, w] : this->widget_map)
    w->reset_value(reset_to_initial_state);

  Q_EMIT this->value_changed();
}

void AttributesWidget::on_restore_save_state()
{
  Logger::log()->trace("AttributesWidget::on_restore_save_state");

  bool reset_to_initial_state = false;

  for (auto &[k, w] : this->widget_map)
    w->reset_value(reset_to_initial_state);

  Q_EMIT this->value_changed();
}

void AttributesWidget::on_save_preset()
{
  Logger::log()->trace("AttributesWidget::on_save_preset");

  QString fname = QFileDialog::getSaveFileName(nullptr,
                                               "preset.json",
                                               ".",
                                               "json file (*.json)");

  if (!fname.isNull() && !fname.isEmpty())
  {
    nlohmann::json json;
    for (auto &[key, pa] : *this->p_attr_map)
      json[key] = pa->json_to();

    std::ofstream file(fname.toStdString());

    if (file.is_open())
    {
      file << json.dump(4);
      file.close();
    }
    else
      Logger::log()->error("Could not open file {} to save JSON", fname.toStdString());
  }
}

void AttributesWidget::on_save_state()
{
  Logger::log()->trace("AttributesWidget::on_save_state");

  for (auto &[key, pa] : *p_attr_map)
    pa->save_state();
}

} // namespace attr
