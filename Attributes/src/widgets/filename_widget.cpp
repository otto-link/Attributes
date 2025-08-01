/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include <QFileDialog>
#include <QLabel>
#include <QVBoxLayout>

#include "attributes/logger.hpp"
#include "attributes/widgets/filename_widget.hpp"
#include "attributes/widgets/widget_utils.hpp"

namespace attr
{

FilenameWidget::FilenameWidget(FilenameAttribute *p_attr) : p_attr(p_attr)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  setup_default_layout_spacing(layout);

  if (this->p_attr->get_label() != "")
  {
    QLabel *label = new QLabel(this->p_attr->get_label().c_str());
    layout->addWidget(label);
  }

  this->button = new QPushButton(this->p_attr->get_value().string().c_str());
  layout->addWidget(this->button);

  this->connect(
      this->button,
      &QPushButton::released,
      [this]()
      {
        std::filesystem::path path = this->p_attr->get_value().parent_path();

        QString fname;

        if (this->p_attr->get_for_saving())
          fname = QFileDialog::getSaveFileName(nullptr,
                                               this->p_attr->get_label().c_str(),
                                               path.string().c_str(),
                                               this->p_attr->get_filter().c_str());
        else
          fname = QFileDialog::getOpenFileName(nullptr,
                                               this->p_attr->get_label().c_str(),
                                               path.string().c_str(),
                                               this->p_attr->get_filter().c_str());

        if (!fname.isNull() && !fname.isEmpty())
        {
          this->p_attr->set_value(fname.toStdString());
          this->update_attribute_from_widget();
        }

        this->button->setToolTip(this->p_attr->get_value().string().c_str());
      });

  this->setLayout(layout);
}

void FilenameWidget::reset_value(bool reset_to_initial_state)
{
  if (reset_to_initial_state)
    this->p_attr->reset_to_initial_state();
  else
    this->p_attr->reset_to_save_state();

  std::string basename = this->p_attr->get_value().filename().string();
  this->button->setText(basename.c_str());
}

void FilenameWidget::update_attribute_from_widget()
{
  Logger::log()->trace("{}", p_attr->to_string());

  std::string basename = this->p_attr->get_value().filename().string();
  this->button->setText(basename.c_str());

  Q_EMIT this->value_changed();
}

} // namespace attr
