/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "attributes/logger.hpp"

namespace gngui
{

// Initialize the static member
std::shared_ptr<spdlog::logger> Logger::instance = nullptr;

std::shared_ptr<spdlog::logger> &Logger::get_logger()
{
  if (!instance)
  {
    instance = spdlog::stdout_color_mt("console_attributes");
    instance->set_pattern("[attr-] [%H:%M:%S] [%^---%L---%$] %v");
    instance->set_level(spdlog::level::trace);
  }
  return instance;
}

} // namespace gngui
