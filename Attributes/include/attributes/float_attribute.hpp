#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class FloatAttribute : public AbstractAttribute
{
public:
  FloatAttribute() = delete;

  FloatAttribute(float              value,
                 float              vmin,
                 float              vmax,
                 const std::string &label = "",
                 const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER)
      : AbstractAttribute(AttributeType::FLOAT, label, bound_check), value(value),
        vmin(vmin), vmax(vmax)
  {
  }

  BoundCheck get_bound_check() const { return this->bound_check; }

  float get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"];
    this->vmin = json["vmin"];
    this->vmax = json["vmax"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["vmin"] = this->vmin;
    json["vmax"] = this->vmax;
    return json;
  }

  void set_value(const float &new_value) { this->value = new_value; }

  std::string to_string() { return std::to_string(this->value); }

private:
  float value;
  float vmin;
  float vmax;
};

} // namespace attr
