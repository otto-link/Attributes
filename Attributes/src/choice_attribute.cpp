/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <algorithm>
#include <stdexcept>

#include "attributes/choice_attribute.hpp"

namespace attr
{

// helpers

void validate_choice_list(const std::vector<std::string> &choice_list)
{
  if (choice_list.empty())
  {
    std::string msg = "Choice list cannot be empty";
    Logger::log()->critical(msg);
    throw std::invalid_argument(msg);
  }
}

void validate_value(const std::vector<std::string> &choice_list, const std::string &value)
{
  if (std::find(choice_list.begin(), choice_list.end(), value) == choice_list.end())
  {
    std::string msg = "Value '" + value + "' is not in the choice list";
    Logger::log()->critical(msg);
    throw std::invalid_argument(msg);
  }
}

// class defition

ChoiceAttribute::ChoiceAttribute(const std::vector<std::string> choice_list,
                                 const std::string             &value)
    : AbstractAttribute(AttributeType::CHOICE, "")
{
  validate_choice_list(choice_list);
  validate_value(choice_list, value);

  this->choice_list = choice_list;
  this->value = value;
}

ChoiceAttribute::ChoiceAttribute(const std::string             &label,
                                 const std::vector<std::string> choice_list,
                                 const std::string             &value)
    : AbstractAttribute(AttributeType::CHOICE, label)
{
  validate_choice_list(choice_list);
  validate_value(choice_list, value);

  this->choice_list = choice_list;
  this->value = value;

  this->save_state();
}

ChoiceAttribute::ChoiceAttribute(const std::string             &label,
                                 const std::vector<std::string> choice_list)
    : AbstractAttribute(AttributeType::CHOICE, label)
{
  validate_choice_list(choice_list);

  this->choice_list = choice_list;
  this->value = choice_list.front();
}

void ChoiceAttribute::json_from(nlohmann::json const &json)
{
  AbstractAttribute::json_from(json);
  this->value = json["value"];
  this->choice_list = json["choice_list"].get<std::vector<std::string>>();
  ;
}

nlohmann::json ChoiceAttribute::json_to() const
{
  nlohmann::json json = AbstractAttribute::json_to();
  json["value"] = this->value;
  json["choice_list"] = this->choice_list;
  return json;
}

std::string ChoiceAttribute::to_string()
{
  std::ostringstream oss;
  oss << "{";
  for (size_t k = 0; k < choice_list.size(); ++k)
  {
    if (value == choice_list[k])
      oss << "[" << choice_list[k] << "]";
    else
      oss << choice_list[k];

    if (k < choice_list.size() - 1)
      oss << ", ";
  }
  oss << "}";
  return oss.str();
}

} // namespace attr
