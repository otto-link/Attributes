#pragma once
#include <string>

#include "attributes/logger.hpp"

namespace attr
{

enum AttributeType
{
  BOOL,
  INT,
  VEC2FLOAT,
  INVALID,
};

enum BoundCheck
{
  UNCHECKED,
  UPPER_ONLY,
  LOWER_ONLY,
  UPPER_LOWER,
};

class AbstractAttribute
{

public:
  AbstractAttribute() = delete;

  AbstractAttribute(const AttributeType &type,
                    const std::string   &label,
                    const BoundCheck    &bound_check)
      : type(type), label(label), bound_check(bound_check)
  {
  }

  std::string get_label() const { return this->label; }

  AttributeType get_type() const { return this->type; }

  template <class T = void> T *get_ref()
  {
    T *ptr = dynamic_cast<T *>(this);
    if (ptr)
      return ptr;
    else
    {
      QATLOG->critical("in Attribute, trying to get an attribute type which is not "
                       "compatible with the current instance. Get type is: [{}]",
                       typeid(T).name());
      throw std::runtime_error("wrong type");
    }
  }

  // virtual void json_from(nlohmann::json const &);

  // virtual nlohmann::json json_to() const;

  void set_label(const std::string &new_label) { this->label = new_label; }

protected:
  AttributeType type = AttributeType::INVALID;
  std::string   label = "";
  BoundCheck    bound_check;
};

} // namespace attr
