#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class IntAttribute : public AbstractAttribute
{
public:
  IntAttribute() = delete;

  IntAttribute(int                value,
               int                vmin,
               int                vmax,
               const std::string &label = "",
               const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER)
      : AbstractAttribute(AttributeType::INT, label, bound_check), value(value),
        vmin(vmin), vmax(vmax)
  {
  }

  std::string to_string() { return std::to_string(this->value); }

  BoundCheck get_bound_check() const { return this->bound_check; }

  int get_value() const { return this->value; }

  int get_vmin() const { return this->vmin; }

  int get_vmax() const { return this->vmax; }

  void set_value(const int &new_value) { this->value = new_value; }

private:
  int value;
  int vmin;
  int vmax;
};

} // namespace attr
