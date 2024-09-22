/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

#include "attributes/helpers.hpp"

namespace attr
{

ValueSliders::BoundMode convert_bound_check(const BoundCheck &bound_check)
{
  ValueSliders::BoundMode bcheck = ValueSliders::BoundMode::UNCHECKED;

  if (bound_check == BoundCheck::UPPER_ONLY)
    bcheck = ValueSliders::BoundMode::UPPER_ONLY;
  else if (bound_check == BoundCheck::LOWER_ONLY)
    bcheck = ValueSliders::BoundMode::LOWER_ONLY;
  else if (bound_check == BoundCheck::UPPER_LOWER)
    bcheck = ValueSliders::BoundMode::UPPER_LOWER;

  return bcheck;
}

} // namespace attr
