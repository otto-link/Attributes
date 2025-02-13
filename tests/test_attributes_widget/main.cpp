#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "attributes.hpp"
#include "attributes/widgets/attributes_widget.hpp"
#include "attributes/widgets/inspector_widget.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  attr::Logger::log()->info("Starting test application...");

  std::map<std::string, std::unique_ptr<attr::AbstractAttribute>> map = {};

  map["bool"] = attr::create_attr<attr::BoolAttribute>(true, "bool", "Bool Checked");
  map["color"] = attr::create_attr<attr::ColorAttribute>(1.f, 0.f, 0.f, 1.f, "color");
  map["float"] = attr::create_attr<attr::FloatAttribute>(1,
                                                         0,
                                                         10,
                                                         "float",
                                                         attr::BoundCheck::UPPER_LOWER);
  map["int"] = attr::create_attr<attr::IntAttribute>(1,
                                                     0,
                                                     10,
                                                     "int",
                                                     attr::BoundCheck::UPPER_LOWER);

  std::map<std::string, int> choices = {{"choice 1", 0}, {"choice 2", 1}};
  map["enum"] = attr::create_attr<attr::MapEnumAttribute>("choice2", choices, "MapEnum");
  // map["range"] = attr::create_attr<attr::RangeAttribute>("remap");
  map["seed"] = attr::create_attr<attr::SeedAttribute>();
  // map["vec2float"] = attr::create_attr<attr::Vec2FloatAttribute>("center");

  map["wave_nb_attr"] = attr::create_attr<attr::WaveNbAttribute>();
  map["fname"] = attr::create_attr<attr::FilenameAttribute>("./toto.csv", "*", "my file");

  if (false)
  {
    std::vector<std::vector<float>> default_gradient = {{0.f, 0.f, 0.f, 0.f, 1.f},
                                                        {1.f, 0.f, 1.f, 0.f, 1.f}};

    map["gradient"] = attr::create_attr<attr::ColorGradientAttribute>("Gradient");
    std::cout << map.at("gradient").get()->to_string() << "\n";
    std::cout << map.at("gradient").get()->json_to().dump(4) << "\n";
  }

  std::vector<float> v0 = {0.2f, 0.5f, 1.f};
  map["vec_float"] = attr::create_attr<attr::VecFloatAttribute>(v0,
                                                                0.f,
                                                                1.f,
                                                                "vec_float");
  std::cout << map.at("vec_float").get()->to_string() << "\n";
  std::cout << map.at("vec_float").get()->json_to().dump(4) << "\n";

  std::vector<int> vi0 = {4, 5, 8};
  map["vec_int"] = attr::create_attr<attr::VecIntAttribute>(vi0, 3, 10, "vec_int");

  // map["hmap"] = attr::create_attr<attr::ArrayAttribute>("hmap",
  //                                                       hmap::Vec2<int>(256, 256));

  auto cloud = hmap::Cloud(10, 0);
  map["zcloud"] = attr::create_attr<attr::CloudAttribute>(cloud, "Cloud");

  // auto path = hmap::Path(); // 10, 1);
  // map["path"] = attr::create_attr<attr::PathAttribute>(path, "Path");

  //
  QMainWindow w;

  // auto brush = attr::get_attribute_widget(map.at("hmap").get());
  // brush->show();

  // auto point = attr::get_attribute_widget(map.at("cloud").get());
  // point->show();

  w.setCentralWidget(new attr::AttributesWidget(&map));

  // QWidget *inspector = new attr::InspectorWidget(&map);
  // inspector->show();

  w.show();

  return app.exec();
}
