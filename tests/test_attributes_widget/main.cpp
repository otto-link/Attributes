#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "attributes.hpp"
#include "attributes/widgets/attributes_widget.hpp"

#include "highmap/primitives.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  attr::Logger::log()->info("Starting test application...");

  std::map<std::string, std::unique_ptr<attr::AbstractAttribute>> map0, map1, map2, map3,
      map4, map5, map6, map7, map8;

  // --- numbers

  // clang-format off
  map0["bool base"] = attr::create_attr<attr::BoolAttribute>("unique label", false);
  map0["bool toggle"] = attr::create_attr<attr::BoolAttribute>("toggle label", "option1 true", "option2 false", true);
  map0["bool toggle no label"] = attr::create_attr<attr::BoolAttribute>("", "option1 true", "option2 false", false);

  map0["int no_bound"] = attr::create_attr<attr::IntAttribute>("label int no_bound", 1);
  map0["int bound_inf"] = attr::create_attr<attr::IntAttribute>("label int bound_inf", 1, 0);
  map0["int bound_sup"] = attr::create_attr<attr::IntAttribute>("label int bound_sup", 1, -INT_MAX, 20, "{} it.");
  map0["int bound_both"] = attr::create_attr<attr::IntAttribute>("label int bound_both", 1, 0, 10);

  map0["float no_bound"] = attr::create_attr<attr::FloatAttribute>("label float no_bound", 1);
  map0["float bound_inf"] = attr::create_attr<attr::FloatAttribute>("label float bound_inf", 1.f, 0.f);
  map0["float bound_sup"] = attr::create_attr<attr::FloatAttribute>("label float bound_sup", 1.f, -FLT_MAX, 20.f, "{:.2f}°");
  map0["float bound_both"] = attr::create_attr<attr::FloatAttribute>("label float bound_both", 1.f, 0.f, 10.f);

  map0["seed0"] = attr::create_attr<attr::SeedAttribute>();
  map0["seed1"] = attr::create_attr<attr::SeedAttribute>("label + default value", 10);
  // clang-format on

  // --- texts and choices

  std::vector<std::string>   choice_list = {"A", "B", "3"};
  std::map<std::string, int> choice_enum = {{"choice 1", 0},
                                            {"choice 2", 1},
                                            {"choice 3", 2}};

  // clang-format off
  map1["fname0"] = attr::create_attr<attr::FilenameAttribute>("my file", "./toto.csv", "*", false);   // load
  map1["fname1"] = attr::create_attr<attr::FilenameAttribute>("", "./toto_no_label.csv", "*", false); // load
  map1["fname2"] = attr::create_attr<attr::FilenameAttribute>("", "./toto_no_label.csv", "*", true);  // save
  
  map1["choice"] = attr::create_attr<attr::ChoiceAttribute>("A list of choice", choice_list, "B");
  map1["enum"] = attr::create_attr<attr::EnumAttribute>("A list of enum", choice_enum, "B");

  map1["str1"] = attr::create_attr<attr::StringAttribute>("string1", "value");
  map1["str2"] = attr::create_attr<attr::StringAttribute>("string2 read_only", "hard value", true);
  // clang-format on

  // --- colors

  // clang-format off
  map2["color1"] = attr::create_attr<attr::ColorAttribute>("label color1", std::vector({1.f, 0.f, 0.f, 1.f}));
  map2["color2"] = attr::create_attr<attr::ColorAttribute>("label color2", 0.f, 1.f, 0.f, 1.f);
  // clang-format on

  std::vector<attr::Stop> default_gradient = {{0.f, 0.f, 0.f, 0.f, 1.f},
                                              {0.5f, 1.f, 0.f, 0.f, 1.f},
                                              {1.f, 0.f, 0.f, 1.f, 1.f}};

  // clang-format off
  map2["gradient0"] = attr::create_attr<attr::ColorGradientAttribute>("Gradient");
  map2["gradient1"] = attr::create_attr<attr::ColorGradientAttribute>("Gradient with input", default_gradient);

  auto *p_a = dynamic_cast<attr::ColorGradientAttribute*>(map2.at("gradient1").get());
  p_a->set_presets({
      attr::Preset({"Rainbow",
		    {{0.f, {0.f, 0.f, 0.f, 1.f}}, {1.f, {1.f, 1.f, 1.f, 1.f}}}})
	});

  p_a->set_description("A description that will\n appear in the tool tip.");

  // clang-format on

  // --- HighMap attributes

  hmap::Array input_array = hmap::white(hmap::Vec2<int>(256, 256), 0.f, 1.f, 0);

  // clang-format off
  map3["array0"] = attr::create_attr<attr::ArrayAttribute>("array label", hmap::Vec2<int>(256, 256));
  map3["array1"] = attr::create_attr<attr::ArrayAttribute>("array label", input_array);

  map4["cloud"] = attr::create_attr<attr::CloudAttribute>("cloud label");
  map4["path"] = attr::create_attr<attr::PathAttribute>("path label");
  // clang-format on

  // --- vector-like attributes

  std::vector<float> kw = {2.f, 4.f};
  std::vector<float> dv = {-1.f, 8.f};

  std::vector<int>   vint = {1, 3, 7, 2};
  std::vector<float> vfloat = {1.f, 3.f, 7.f, 2.f};

  // clang-format off
  map5["wnb0"] = attr::create_attr<attr::WaveNbAttribute>();
  map5["wnb1"] = attr::create_attr<attr::WaveNbAttribute>("lower bound", kw, 0.f, FLT_MAX, false);
  map5["wnb2"] = attr::create_attr<attr::WaveNbAttribute>("upper bound", kw, -FLT_MAX, 16.f, false);
  map5["wnb3"] = attr::create_attr<attr::WaveNbAttribute>("both bound", kw, 0.f, 16.f, false);

  map5["range0"] =  attr::create_attr<attr::RangeAttribute>();
  map5["range1"] =  attr::create_attr<attr::RangeAttribute>("range label", false);
  map5["range2"] =  attr::create_attr<attr::RangeAttribute>("range label2", dv, -2.f, 10.f);

  map6["v2f0"] = attr::create_attr<attr::Vec2FloatAttribute>("label center");
  map6["v2f1"] = attr::create_attr<attr::Vec2FloatAttribute>("label center XY", dv, -2.f, 3.f, -15.f, 20.f);

  map7["vec_int"] = attr::create_attr<attr::VecIntAttribute>("vec_int", vint, -4, 10);
  map7["vec_float"] = attr::create_attr<attr::VecFloatAttribute>("vec_float", vfloat, -4.f, 10.f);
  // clang-format on

  // clang-format off
  map8["res0"] = attr::create_attr<attr::ResolutionAttribute>("res", 256, 512, true, true);
  // clang-format on

  if (false)
  {
    QMainWindow w;
    w.setCentralWidget(new attr::AttributesWidget(&map0));
    w.show();
  }

  // auto brush = attr::get_attribute_widget(map.at("hmap").get());
  // brush->show();

  // auto point = attr::get_attribute_widget(map.at("cloud").get());
  // point->show();

  // auto aw0 = new attr::AttributesWidget(&map0);
  // aw0->show();

  // auto aw1 = new attr::AttributesWidget(&map1, nullptr, "Custom TITLE", true);
  // aw1->show();

  // auto aw2 = new attr::AttributesWidget(&map2);
  // aw2->show();

  // auto aw3 = new attr::AttributesWidget(&map3);
  // aw3->show();

  // auto aw4 = new attr::AttributesWidget(&map4);
  // aw4->show();

  // auto aw5 = new attr::AttributesWidget(&map5);
  // aw5->show();

  std::vector<std::string> attr_key_list = {"v2f0",
                                            "_SEPARATOR_TEXT_The section title",
                                            "v2f1"};

  // auto aw6 = new attr::AttributesWidget(&map6, &attr_key_list, "", true);
  // aw6->show();

  // auto aw7 = new attr::AttributesWidget(&map7);
  // aw7->show();

  auto aw8 = new attr::AttributesWidget(&map8);
  aw8->show();

  return app.exec();
}
