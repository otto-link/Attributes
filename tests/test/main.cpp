#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "attributes/logger.hpp"

#include "attributes/bool_attribute.hpp"
#include "attributes/int_attribute.hpp"
#include "attributes/vec2float_attribute.hpp"
#include "attributes/widgets/bool_widget.hpp"
#include "attributes/widgets/int_widget.hpp"
#include "attributes/widgets/vec2float_widget.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QATLOG->info("Starting test application...");

  auto bool_attr = attr::BoolAttribute(true, "Bool", "Bool Checked");
  auto int_attr = attr::IntAttribute(1, 0, 10, "Int", attr::BoundCheck::LOWER_ONLY);

  auto vec2float_attr = attr::Vec2FloatAttribute({-0.5f, 1.8f},
                                                 -1.f,
                                                 1.f,
                                                 -2.f,
                                                 2.f,
                                                 "Vec2Float");

  bool_attr.json_to();
  int_attr.json_to();
  vec2float_attr.json_to();

  QMainWindow w;
  QWidget     wrapper;
  QVBoxLayout layout;
  wrapper.setLayout(&layout);

  layout.addWidget(new QLabel("Attributes"));

  layout.addWidget(new attr::BoolWidget(&bool_attr));
  layout.addWidget(new attr::IntWidget(&int_attr));
  layout.addWidget(new attr::Vec2FloatWidget(&vec2float_attr));

  w.setCentralWidget(&wrapper);

  w.show();

  return app.exec();
}
