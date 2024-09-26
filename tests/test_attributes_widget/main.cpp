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

  map["range"] = attr::create_attr<attr::RangeAttribute>("remap");
  map["seed"] = attr::create_attr<attr::SeedAttribute>();
  map["vec2float"] = attr::create_attr<attr::Vec2FloatAttribute>("center");
  map["wave_nb_attr"] = attr::create_attr<attr::WaveNbAttribute>();

  map["fname"] = attr::create_attr<attr::FilenameAttribute>("./toto.csv", "*", "my file");

  map["fname"]->json_to();

  QMainWindow w;

  w.setCentralWidget(new attr::AttributesWidget(&map));

  QWidget *inspector = new attr::InspectorWidget(&map);
  inspector->show();

  w.show();

  return app.exec();
}
