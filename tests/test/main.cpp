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

  attr::BoolAttribute bool_attr(true, "Enable Feature");
  attr::IntAttribute  int_attr(1, 0, 100, "Integer"); // in [0, 100]

  QVBoxLayout layout;

  layout.addWidget(attr::get_attribute_widget(&bool_attr));
  layout.addWidget(attr::get_attribute_widget(&int_attr));

  window.setLayout(&layout);
  window.show();

  return app.exec();
}
