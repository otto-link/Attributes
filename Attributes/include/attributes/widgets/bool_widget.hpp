#pragma once
#include <QHBoxLayout>
#include <QPushButton>

#include "attributes/bool_attribute.hpp"
#include "attributes/logger.hpp"

namespace attr
{

class BoolWidget : public QWidget
{
  Q_OBJECT

public:
  BoolWidget() = default;

  BoolWidget(BoolAttribute *p_attr) : p_attr(p_attr)
  {
    this->button = new QPushButton(p_attr->get_label().c_str());
    this->button->setCheckable(true);
    this->button->setChecked(this->p_attr->get_value());

    this->connect(this->button,
                  &QPushButton::toggled,
                  [this]()
                  {
                    this->update_attribute_from_widget();

                    // update label according to value
                    if (this->p_attr->get_value())
                      this->button->setText(this->p_attr->get_label_checked().c_str());
                    else
                      this->button->setText(this->p_attr->get_label().c_str());
                  });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(this->button);
    this->setLayout(layout);
  }

Q_SIGNALS:
  void value_changed();

private:
  BoolAttribute *p_attr;

  QPushButton *button;

  void update_attribute_from_widget()
  {
    this->p_attr->set_value(this->button->isChecked());
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
