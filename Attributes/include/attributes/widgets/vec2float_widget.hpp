#pragma once
#include <QHBoxLayout>

#include "attributes/logger.hpp"
#include "attributes/vec2float_attribute.hpp"

namespace attr
{

class Vec2FloatWidget : public QWidget
{
  Q_OBJECT

public:
  Vec2FloatWidget() = default;

  Vec2FloatWidget(Vec2FloatAttribute *p_attr) : p_attr(p_attr) {}

Q_SIGNALS:
  void value_changed();

private:
  Vec2FloatAttribute *p_attr;

  // QPointF value() const { return point; }

  void update_attribute_from_widget()
  {
    // this->p_attr->set_value(this->slider->getVal());
    QATLOG->trace("{}", p_attr->to_string());
    Q_EMIT this->value_changed();
  }
};

} // namespace attr
