/* Copyright (c) 2024 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#pragma once

#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace attr
{

class Logger
{
public:
  static std::shared_ptr<spdlog::logger> &log();

private:
  // Private constructor to prevent direct instantiation
  Logger() = default;

  // Disable copy constructor
  Logger(const Logger &) = delete;

  // Disable assignment operator
  Logger &operator=(const Logger &) = delete;

  // Static member to hold the singleton instance
  static std::shared_ptr<spdlog::logger> instance;
};

} // namespace attr
