#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "attributes/logger.hpp"

#include "attributes/bool_attribute.hpp"
#include "attributes/color_attribute.hpp"
#include "attributes/float_attribute.hpp"
#include "attributes/int_attribute.hpp"
#include "attributes/map_enum_attribute.hpp"
#include "attributes/range_attribute.hpp"
#include "attributes/seed_attribute.hpp"
#include "attributes/vec2float_attribute.hpp"
#include "attributes/wave_nb_attribute.hpp"
#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/color_widget.hpp"
#include "attributes/widgets/float_widget.hpp"
#include "attributes/widgets/int_widget.hpp"
#include "attributes/widgets/map_enum_widget.hpp"
#include "attributes/widgets/range_widget.hpp"
#include "attributes/widgets/seed_widget.hpp"
#include "attributes/widgets/vec2float_widget.hpp"
#include "attributes/widgets/wave_nb_widget.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QATLOG->info("Starting test application...");

  auto bool_attr = attr::BoolAttribute(true, "Bool", "Bool Checked");
  auto color_attr = attr::ColorAttribute({1.f, 0.f, 0.f, 1.f}, "Color");
  auto float_attr = attr::FloatAttribute(1,
                                         0,
                                         10,
                                         "Float",
                                         attr::BoundCheck::UPPER_LOWER);

  auto int_attr = attr::IntAttribute(1, 0, 10, "Int", attr::BoundCheck::LOWER_ONLY);

  std::map<std::string, int> map = {{"choice 1", 0}, {"choice 2", 1}};

  auto map_enum_attr = attr::MapEnumAttribute("choice2", map, "MapEnum");

  // auto range_attr = attr::RangeAttribute({0.5f, 1.2f},
  //                                        -1.f,
  //                                        3.f,
  //                                        "Range",
  //                                        false,
  //                                        attr::BoundCheck::UPPER_LOWER);

  auto range_attr = attr::RangeAttribute();

  // auto seed_attr = attr::SeedAttribute(1, "Seed");
  auto seed_attr = attr::SeedAttribute();

  auto vec2float_attr = attr::Vec2FloatAttribute({-0.5f, 1.8f},
                                                 -1.f,
                                                 1.f,
                                                 -2.f,
                                                 2.f,
                                                 "Vec2Float");

  // auto wave_nb_attr = attr::WaveNbAttribute({0.5f, 1.2f},
  //                                           -1.f,
  //                                           3.f,
  //                                           true,
  //                                           "WaveNb",
  //                                           attr::BoundCheck::UPPER_LOWER);
  auto wave_nb_attr = attr::WaveNbAttribute();

  bool_attr.json_to();
  color_attr.json_to();
  float_attr.json_to();
  int_attr.json_to();
  map_enum_attr.json_to();
  range_attr.json_to();
  seed_attr.json_to();
  vec2float_attr.json_to();
  wave_nb_attr.json_to();

  QMainWindow w;
  QWidget     wrapper;
  QVBoxLayout layout;
  wrapper.setLayout(&layout);

  layout.addWidget(new QLabel("Attributes"));

  layout.addWidget(new attr::BoolWidget(&bool_attr));
  layout.addWidget(new attr::ColorWidget(&color_attr));
  layout.addWidget(new attr::FloatWidget(&float_attr));
  layout.addWidget(new attr::IntWidget(&int_attr));
  layout.addWidget(new attr::MapEnumWidget(&map_enum_attr));
  layout.addWidget(new attr::RangeWidget(&range_attr));
  layout.addWidget(new attr::SeedWidget(&seed_attr));
  layout.addWidget(new attr::Vec2FloatWidget(&vec2float_attr));
  layout.addWidget(new attr::WaveNbWidget(&wave_nb_attr));

  w.setCentralWidget(&wrapper);

  w.show();

  return app.exec();
}
