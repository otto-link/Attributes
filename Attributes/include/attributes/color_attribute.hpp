#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class ColorAttribute : public AbstractAttribute
{
public:
  ColorAttribute() = delete;

  ColorAttribute(std::vector<float> value,
                 const std::string &label = "",
                 const BoundCheck  &bound_check = BoundCheck::UNCHECKED)
      : AbstractAttribute(AttributeType::COLOR, label, bound_check), value(value)
  {
  }

  std::vector<float> get_value() const { return this->value; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"].get<std::vector<float>>();
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    return json;
  }

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string()
  {
    std::string str = "{";

    // Iterate through the vector and concatenate values
    for (size_t i = 0; i < this->value.size(); ++i)
    {
      if (i > 0)
        str += ", ";
      str += std::to_string(this->value[i]);
    }
    return str + "}";
  }

private:
  std::vector<float> value = {1.f, 1.f, 1.f, 1.f};
};

} // namespace attr
