/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file abstract_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QWidget>

namespace attr
{

class AbstractWidget : public QWidget
{
  Q_OBJECT

public:
  AbstractWidget() = default;

Q_SIGNALS:
  void value_changed();
};

} // namespace attr