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

  std::string get_label_checked() const { return this->label_checked; }

  bool get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"];
    this->label_checked = json["label_checked"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["label_checked"] = this->label_checked;
    std::cout << json.dump(4) << "\n";
    return json;
  }

  void set_value(const bool &new_value) { this->value = new_value; }

  std::string to_string() { return this->value ? "true" : "false"; }

private:
  bool        value;
  std::string label_checked;
};

} // namespace attr
