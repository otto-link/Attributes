#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class BoolAttribute : public AbstractAttribute
{
public:
  BoolAttribute() = delete;

  BoolAttribute(bool value)
      : AbstractAttribute(AttributeType::BOOL, "", BoundCheck::UNCHECKED), value(value),
        label_checked("")
  {
  }

  BoolAttribute(bool value, const std::string &label)
      : AbstractAttribute(AttributeType::BOOL, label, BoundCheck::UNCHECKED),
        value(value), label_checked(label)
  {
  }

  BoolAttribute(bool value, const std::string &label, const std::string &label_checked)
      : AbstractAttribute(AttributeType::BOOL, label, BoundCheck::UNCHECKED),
        value(value), label_checked(label_checked)
  {
  }

  std::string to_string() { return this->value ? "true" : "false"; }

  std::string get_label_checked() const { return this->label_checked; }

  bool get_value() const { return this->value; }

  void set_value(const bool &new_value) { this->value = new_value; }

private:
  bool        value;
  std::string label_checked;
};

} // namespace attr
