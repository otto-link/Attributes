/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "attributes/widgets/attributes_widget.hpp"

#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/color_widget.hpp"
#include "attributes/widgets/filename_widget.hpp"
#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/int_widget.hpp"
#include "attributes/widgets/map_enum_widget.hpp"
#include "attributes/widgets/range_widget.hpp"
#include "attributes/widgets/seed_widget.hpp"
#include "attributes/widgets/vec2float_widget.hpp"
#include "attributes/widgets/wave_nb_widget.hpp"

#define RETURN_IF_MATCH(attr_type, widget_class, attribute_class, p_attr)                \
  if ((p_attr)->get_type() == AttributeType::attr_type)                                  \
    return new widget_class(dynamic_cast<attribute_class *>((p_attr)));

namespace attr
{

QWidget *get_attribute_widget(AbstractAttribute *p_attr)
{
  RETURN_IF_MATCH(BOOL, BoolWidget, BoolAttribute, p_attr);
  RETURN_IF_MATCH(COLOR, ColorWidget, ColorAttribute, p_attr);
  RETURN_IF_MATCH(FILENAME, FilenameWidget, FilenameAttribute, p_attr);
  RETURN_IF_MATCH(FLOAT, FloatWidget, FloatAttribute, p_attr);
  RETURN_IF_MATCH(INT, IntWidget, IntAttribute, p_attr);
  RETURN_IF_MATCH(MAP_ENUM, MapEnumWidget, MapEnumAttribute, p_attr);
  RETURN_IF_MATCH(RANGE, RangeWidget, RangeAttribute, p_attr);
  RETURN_IF_MATCH(SEED, SeedWidget, SeedAttribute, p_attr);
  RETURN_IF_MATCH(VEC2FLOAT, Vec2FloatWidget, Vec2FloatAttribute, p_attr);
  RETURN_IF_MATCH(WAVE_NB, WaveNbWidget, WaveNbAttribute, p_attr);

  Logger::get_logger()->warn("Could not find any widget for the attribute type: {} ({})",
                             p_attr->get_type(),
                             attribute_type_map.at(p_attr->get_type()));

  return nullptr;
}

QWidget *get_attribute_widget(std::vector<AbstractAttribute *> p_attributes,
                              const std::string               &label,
                              bool                             horizontal_layout)
{
  QWidget *main_widget = new QWidget();

  QBoxLayout *layout;

  if (horizontal_layout)
    layout = new QHBoxLayout(main_widget);
  else
    layout = new QVBoxLayout(main_widget);

  if (label != "")
    layout->addWidget(new QLabel(label.c_str()));

  for (auto &pa : p_attributes)
    layout->addWidget(get_attribute_widget(pa));

  main_widget->setLayout(layout);

  return main_widget;
}

} // namespace attr