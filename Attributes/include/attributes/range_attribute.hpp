#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class RangeAttribute : public AbstractAttribute
{
public:
  RangeAttribute() = delete;

  RangeAttribute(std::vector<float> value,
                 float              vmin,
                 float              vmax,
                 const std::string &label = "",
                 bool               is_active = true,
                 const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER)
      : AbstractAttribute(AttributeType::RANGE, label, bound_check), value(value),
        vmin(vmin), vmax(vmax), is_active(is_active)
  {
  }

  BoundCheck get_bound_check() const { return this->bound_check; }

  bool get_is_active() const { return this->is_active; }

  std::vector<float> get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"].get<std::vector<float>>();
    this->vmin = json["vmin"];
    this->vmax = json["vmax"];
    this->is_active = json["is_active"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["vmin"] = this->vmin;
    json["vmax"] = this->vmax;
    json["is_active"] = this->is_active;
    std::cout << json.dump(4) << "\n";
    return json;
  }

  void set_is_active(bool new_state) { this->is_active = new_state; }

  void set_value(const std::vector<float> &new_value) { this->value = new_value; }

  std::string to_string()
  {
    std::string str = "{";
    str += std::to_string(this->value[0]);
    str += ", ";
    str += std::to_string(this->value[1]);
    str += "}";
    return str;
  }

private:
  std::vector<float> value;
  float              vmin;
  float              vmax;
  bool               is_active;
};

} // namespace attr
