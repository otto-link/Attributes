#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class WaveNbAttribute : public AbstractAttribute
{
public:
  WaveNbAttribute() = delete;

  WaveNbAttribute(std::vector<float> value,
                  float              vmin,
                  float              vmax,
                  bool               link_xy = true,
                  const std::string &label = "",
                  const BoundCheck  &bound_check = BoundCheck::UPPER_LOWER)
      : AbstractAttribute(AttributeType::WAVE_NB, label, bound_check), value(value),
        vmin(vmin), vmax(vmax), link_xy(link_xy)
  {
  }

  BoundCheck get_bound_check() const { return this->bound_check; }

  bool get_link_xy() const { return this->link_xy; }

  std::vector<float> get_value() const { return this->value; }

  float get_vmin() const { return this->vmin; }

  float get_vmax() const { return this->vmax; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"].get<std::vector<float>>();
    this->vmin = json["vmin"];
    this->vmax = json["vmax"];
    this->link_xy = json["link_xy"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["vmin"] = this->vmin;
    json["vmax"] = this->vmax;
    json["link_xy"] = this->link_xy;
    std::cout << json.dump(4) << "\n";
    return json;
  }

  void set_link_xy(const bool new_state) { this->link_xy = new_state; }

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
  std::vector<float> value;
  float              vmin;
  float              vmax;
  bool               link_xy;
};

} // namespace attr
