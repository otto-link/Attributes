#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

#include "attributes.hpp"
#include "attributes/widgets/attributes_widget.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QWidget window;
  window.setWindowTitle("Attributes Demo");

  attr::BoolAttribute bool_attr("Enable Feature", true);
  attr::IntAttribute  int_attr("Integer", 1, 0, 100); // in [0, 100]

  QVBoxLayout layout;

  layout.addWidget(attr::get_attribute_widget(&bool_attr));
  layout.addWidget(attr::get_attribute_widget(&int_attr));

  window.setLayout(&layout);
  window.show();

  return app.exec();
}
