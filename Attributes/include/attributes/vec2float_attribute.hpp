#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class Vec2FloatAttribute : public AbstractAttribute
{
public:
  Vec2FloatAttribute() = delete;

  Vec2FloatAttribute(std::vector<float> value,
                     int                xmin,
                     int                xmax,
                     int                ymin,
                     int                ymax,
                     const std::string &label = "")
      : AbstractAttribute(AttributeType::VEC2FLOAT, label, BoundCheck::UNCHECKED),
        value(value), xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax)
  {
  }

  std::string to_string()
  {
    std::string str = "{";
    str += std::to_string(this->value[0]);
    str += ", ";
    str += std::to_string(this->value[1]);
    str += "}";
    return str;
  }

  BoundCheck get_bound_check() const { return this->bound_check; }

  std::vector<float> get_value() const { return this->value; }

  int get_xmin() const { return this->xmin; }

  int get_xmax() const { return this->xmax; }

  int get_ymin() const { return this->ymin; }

  int get_ymax() const { return this->ymax; }

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

private:
  std::vector<float> value;
  float              xmin, xmax;
  float              ymin, ymax;
};

} // namespace attr
