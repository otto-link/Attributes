/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>

#include "attributes/logger.hpp"
#include "attributes/widgets/abstract_widget.hpp"

namespace attr
{

bool AbstractWidget::event(QEvent *event)
{
  if (event->type() == QEvent::ToolTip && this->tool_tip_fct)
  {
    auto *helpEvent = static_cast<QHelpEvent *>(event);

    QString tip_text = this->tool_tip_fct().c_str();
    QToolTip::showText(helpEvent->globalPos(), tip_text, this);

    return true; // event handled
  }

  return QWidget::event(event);
}

void AbstractWidget::set_tool_tip_fct(std::function<std::string()> new_fct)
{
  this->tool_tip_fct = new_fct;
}

} // namespace attr
