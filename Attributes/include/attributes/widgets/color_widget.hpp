#pragma once
#include <QColorDialog>
#include <QGridLayout>
#include <QLabel>

#include "attributes/color_attribute.hpp"
#include "attributes/logger.hpp"

namespace attr
{

class ColorWidget : public QWidget
{
  Q_OBJECT

public:
  ColorWidget() = delete;

  ColorWidget(ColorAttribute *p_attr) : p_attr(p_attr)
  {
    QGridLayout *layout = new QGridLayout(this);

    // main label
    layout->addWidget(new QLabel(this->p_attr->get_label().c_str()), 0, 0, 1, 2);

    // color label
    this->label = new QLabel();

    int r = (int)(255.f * this->p_attr->get_value()[0]);
    int g = (int)(255.f * this->p_attr->get_value()[1]);
    int b = (int)(255.f * this->p_attr->get_value()[2]);
    int a = (int)(255.f * this->p_attr->get_value()[3]);

    std::string str = "QWidget {background-color: rgba(" + std::to_string(r) + ", " +
                      std::to_string(g) + ", " + std::to_string(b) + ", " +
                      std::to_string(a) + ");}";

    this->label->setStyleSheet(str.c_str());
    layout->addWidget(this->label, 1, 1, 1, 2);

    // color picking button
    QPushButton *button = new QPushButton("Pick color");
    layout->addWidget(button, 1, 0);

    connect(button,
            &QPushButton::released,
            [this]()
            {
              QColorDialog color_dialog;
              color_dialog.setOption(QColorDialog::ShowAlphaChannel);
              QColor color = color_dialog.getColor();

              if (color.isValid())
                this->update_attribute_from_widget(color);
            });

    this->setLayout(layout);
  }

Q_SIGNALS:
  void value_changed();

private:
  ColorAttribute *p_attr;

  QLabel *label;

  void update_attribute_from_widget(QColor color)
  {
    std::vector<float> vec(4);

    vec[0] = (float)color.red() / 255.f;
    vec[1] = (float)color.green() / 255.f;
    vec[2] = (float)color.blue() / 255.f;
    vec[3] = (float)color.alpha() / 255.f;

    this->p_attr->set_value(vec);

    std::string str = "QWidget {background-color: rgba(" + std::to_string(color.red()) +
                      ", " + std::to_string(color.green()) + ", " +
                      std::to_string(color.blue()) + ", " +
                      std::to_string(color.alpha()) + ");}";

    this->label->setStyleSheet(str.c_str());

    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
