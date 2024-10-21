/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QVBoxLayout>

#include "attributes/widgets/attributes_widget.hpp"

#include "attributes/widgets/array_widget.hpp"
#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/cloud_widget.hpp"
#include "attributes/widgets/color_gradient_widget.hpp"
#include "attributes/widgets/color_widget.hpp"
#include "attributes/widgets/filename_widget.hpp"
#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/int_widget.hpp"
#include "attributes/widgets/map_enum_widget.hpp"
#include "attributes/widgets/path_widget.hpp"
#include "attributes/widgets/range_widget.hpp"
#include "attributes/widgets/seed_widget.hpp"
#include "attributes/widgets/vec2float_widget.hpp"
#include "attributes/widgets/vec_float_widget.hpp"
#include "attributes/widgets/wave_nb_widget.hpp"

#define RETURN_IF_MATCH(attr_type, widget_class, attribute_class, p_attr)                \
  if ((p_attr)->get_type() == AttributeType::attr_type)                                  \
    return new widget_class(dynamic_cast<attribute_class *>((p_attr)));

namespace attr
{

AbstractWidget *get_attribute_widget(AbstractAttribute *p_attr)
{
  RETURN_IF_MATCH(BOOL, BoolWidget, BoolAttribute, p_attr);
  RETURN_IF_MATCH(COLOR, ColorWidget, ColorAttribute, p_attr);
  RETURN_IF_MATCH(COLOR_GRADIENT, ColorGradientWidget, ColorGradientAttribute, p_attr);
  RETURN_IF_MATCH(FILENAME, FilenameWidget, FilenameAttribute, p_attr);
  RETURN_IF_MATCH(FLOAT, FloatWidget, FloatAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_ARRAY, ArrayWidget, ArrayAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_CLOUD, CloudWidget, CloudAttribute, p_attr);
  RETURN_IF_MATCH(HMAP_PATH, PathWidget, PathAttribute, p_attr);
  RETURN_IF_MATCH(INT, IntWidget, IntAttribute, p_attr);
  RETURN_IF_MATCH(MAP_ENUM, MapEnumWidget, MapEnumAttribute, p_attr);
  RETURN_IF_MATCH(RANGE, RangeWidget, RangeAttribute, p_attr);
  RETURN_IF_MATCH(SEED, SeedWidget, SeedAttribute, p_attr);
  RETURN_IF_MATCH(VEC_FLOAT, VecFloatWidget, VecFloatAttribute, p_attr);
  RETURN_IF_MATCH(VEC2FLOAT, Vec2FloatWidget, Vec2FloatAttribute, p_attr);
  RETURN_IF_MATCH(WAVE_NB, WaveNbWidget, WaveNbAttribute, p_attr);

  Logger::log()->warn("Could not find any widget for the attribute type requested");

  return nullptr;
}

AttributesWidget::AttributesWidget(
    std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map,
    std::vector<std::string>                                  *p_attr_ordered_key)
    : p_attr_map(p_attr_map), p_attr_ordered_key(p_attr_ordered_key)
{
  this->setWindowTitle("Attribute settings");

  // define the attribute order either on the key map order or on a
  // given order provided as a key list (optional)
  std::vector<std::string> attr_key_queue = {};
  bool                     check_count = false;

  for (auto &[k, v] : *p_attr_map)
    attr_key_queue.push_back(k);

  if (p_attr_ordered_key)
    if (p_attr_ordered_key->size() > 0)
    {
      attr_key_queue = *p_attr_ordered_key;
      check_count = true;
    }

  // setup layout
  QVBoxLayout *layout = new QVBoxLayout(this);

  // update button
  QPushButton *update_button = new QPushButton("Force update");
  layout->addWidget(update_button);

  connect(update_button,
          &QPushButton::released,
          [this]() { Q_EMIT this->update_button_released(); });

  // to check the number of widgets corresponds to the number of keys
  // in "p_attr_ordered_key"
  int count = 0;

  for (auto &key : attr_key_queue)
  {
    if (key == "_SEPARATOR_")
    {
      QFrame *line = new QFrame;
      line->setFrameShape(QFrame::HLine);
      line->setFrameShadow(QFrame::Plain);
      line->setFixedHeight(1);
      layout->addWidget(line);
    }
    else if (p_attr_map->contains(key))
    {
      AbstractAttribute *p_attr = p_attr_map->at(key).get();
      AbstractWidget    *widget = get_attribute_widget(p_attr);
      layout->addWidget(widget);

      this->connect(widget,
                    &AbstractWidget::value_changed,
                    [this, p_attr]() { Q_EMIT this->value_changed(); });

      count++;
    }
    else
    {
      Logger::log()->critical(
          "unknown attribute key {} in AttributesWidget (check attr_ordered_key)",
          key);
    }
  }

  if (check_count && count != (int)this->p_attr_map->size())
  {
    Logger::log()->critical(
        "missing attributes in AttributesWidget (check attr_ordered_key)");
    throw std::runtime_error(
        "missing attributes in AttributesWidget (check attr_ordered_key)");
  }

  // as a last resort, for empty "settings"
  if (p_attr_map->size() == 0)
  {
    QLabel *widget = new QLabel("no settings");
    QFont   f = widget->font();
    f.setItalic(true);
    widget->setFont(f);
    layout->addWidget(widget);
  }

  this->setLayout(layout);
}

} // namespace attr
