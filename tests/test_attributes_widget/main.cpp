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

  // --- start with base attributes

  std::map<std::string, std::unique_ptr<attr::AbstractAttribute>> map0 = {};

  // bool
  map0["bool base"] = attr::create_attr<attr::BoolAttribute>("unique label", false);
  map0["bool toggle"] = attr::create_attr<attr::BoolAttribute>("option1",
                                                               "option2",
                                                               false);

  // int
  map0["int no_bound"] = attr::create_attr<attr::IntAttribute>("label int no_bound", 1);

  map0["int bound_inf"] = attr::create_attr<attr::IntAttribute>("label int bound_inf",
                                                                1,
                                                                0);
  map0["int bound_sup"] = attr::create_attr<attr::IntAttribute>("label int bound_sup",
                                                                1,
                                                                INT_MIN,
                                                                20);
  map0["int bound_both"] = attr::create_attr<attr::IntAttribute>("label int bound_both",
                                                                 1,
                                                                 0,
                                                                 10);

  std::cout << map0.at("int bound_inf").get()->json_to().dump(4) << "\n";

  // float

  std::vector<std::string> choice_list = {"A", "B", "3"};
  map0["choice"] = attr::create_attr<attr::ChoiceAttribute>("A list of choice",
                                                            choice_list,
                                                            "B");

  std::cout << map0.at("choice").get()->to_string() << "\n";
  std::cout << map0.at("choice").get()->json_to().dump(4) << "\n";

  // map0["float"] = attr::create_attr<attr::FloatAttribute>(1,
  //                                                        0,
  //                                                        10,
  //                                                        "float",
  //                                                        attr::BoundCheck::UPPER_LOWER);

  // --- more complex attributes

  std::map<std::string, std::unique_ptr<attr::AbstractAttribute>> map = {};

  map["color"] = attr::create_attr<attr::ColorAttribute>(1.f, 0.f, 0.f, 1.f, "color");

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
  // QMainWindow w;
  // w.setCentralWidget(new attr::AttributesWidget(&map));
  // w.show();

  // auto brush = attr::get_attribute_widget(map.at("hmap").get());
  // brush->show();

  // auto point = attr::get_attribute_widget(map.at("cloud").get());
  // point->show();

  auto aw0 = new attr::AttributesWidget(&map0);
  aw0->show();

  // QWidget *inspector = new attr::InspectorWidget(&map);
  // inspector->show();

  return app.exec();
}
