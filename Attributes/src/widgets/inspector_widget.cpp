/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QTextEdit>
#include <QTextTable>

#include "attributes/widgets/inspector_widget.hpp"

namespace attr
{

InspectorWidget::InspectorWidget(
    std::map<std::string, std::unique_ptr<AbstractAttribute>> *p_attr_map)
    : p_attr_map(p_attr_map)
{
  QTextEdit *text_edit = new QTextEdit(this);
  text_edit->setReadOnly(true);
  text_edit->setMinimumWidth(256);
  text_edit->setMinimumHeight(256);
  QTextCursor cursor = text_edit->textCursor();

  // setup table
  QTextTableFormat tableFormat;
  tableFormat.setBorder(1);
  tableFormat.setCellPadding(0);
  tableFormat.setCellSpacing(0);

  QTextTable *table = cursor.insertTable((int)p_attr_map->size(), 2, tableFormat);

  // fill table
  int row = 0;

  for (auto &[key, pa] : *this->p_attr_map)
  {

    QTextTableCell cell = table->cellAt(row, 0);
    QTextCursor    cell_cursor = cell.firstCursorPosition();
    cell_cursor.insertText(key.c_str());

    std::string str = pa->json_to().dump(4);
    cell = table->cellAt(row, 1);
    cell_cursor = cell.firstCursorPosition();
    cell_cursor.insertText(str.c_str());

    row++;
  }
}

} // namespace attr
