/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file map_enum_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QComboBox>
#include <QHBoxLayout>

#include "attributes/helpers.hpp"
#include "attributes/logger.hpp"
#include "attributes/map_enum_attribute.hpp"

namespace attr
{

class MapEnumWidget : public QWidget
{
  Q_OBJECT

public:
  MapEnumWidget() = delete;

  MapEnumWidget(MapEnumAttribute *p_attr);

Q_SIGNALS:
  void value_changed();

private:
  MapEnumAttribute *p_attr;

  QComboBox *combobox;

  void update_attribute_from_widget();
};

} // namespace attr
