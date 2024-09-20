#pragma once
#include "attributes/abstract_attribute.hpp"

namespace attr
{

class Vec2FloatAttribute : public AbstractAttribute
{
public:
  Vec2FloatAttribute() = delete;

  Vec2FloatAttribute(std::vector<float> value,
                     float              xmin,
                     float              xmax,
                     float              ymin,
                     float              ymax,
                     const std::string &label = "")
      : AbstractAttribute(AttributeType::VEC2FLOAT, label, BoundCheck::UNCHECKED),
        value(value), xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax)
  {
  }

  BoundCheck get_bound_check() const { return this->bound_check; }

  std::vector<float> get_value() const { return this->value; }

  float get_xmin() const { return this->xmin; }

  float get_xmax() const { return this->xmax; }

  float get_ymin() const { return this->ymin; }

  float get_ymax() const { return this->ymax; }

  void json_from(nlohmann::json const &json) override
  {
    AbstractAttribute::json_from(json);
    this->value = json["value"].get<std::vector<float>>();
    this->xmin = json["xmin"];
    this->xmax = json["xmax"];
    this->ymin = json["ymin"];
    this->ymax = json["ymax"];
  }

  nlohmann::json json_to() const override
  {
    nlohmann::json json = AbstractAttribute::json_to();
    json["value"] = this->value;
    json["xmin"] = this->xmin;
    json["xmax"] = this->xmax;
    json["ymin"] = this->ymin;
    json["ymax"] = this->ymax;
    std::cout << json.dump(4) << "\n";
    return json;
  }

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
  float              xmin, xmax;
  float              ymin, ymax;
};

} // namespace attr
