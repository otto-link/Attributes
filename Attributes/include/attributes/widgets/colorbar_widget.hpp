/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */

/**
 * @file color_gradient_widget.hpp
 * @author Otto Link (otto.link.bv@gmail.com)
 * @brief
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <QLabel>

namespace attr
{

class ColorbarWidget : public QLabel
{
public:
  ColorbarWidget(QWidget *parent = nullptr);

  ColorbarWidget(std::vector<std::vector<float>> colors,
                 QString                         caption = "",
                 QWidget                        *parent = nullptr);

  QString get_caption() { return this->caption; };

  std::vector<std::vector<float>> get_colors() { return this->colors; };

  void set_border(int width, QColor color);

  void set_caption(QString new_caption);

  void update_colors(std::vector<std::vector<float>> new_colors);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  std::vector<std::vector<float>> colors;
  QString                         caption = "";
  int                             border_width = 0;
  QColor                          border_color = Qt::white;
};

} // namespace attr