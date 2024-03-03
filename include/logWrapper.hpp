#pragma once

#ifndef LOGWRAPPER_HPP_
#define LOGWRAPPER_HPP_

#ifndef FLECTION_NO_LOG
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#endif

#include <memory>
#include <utility>

#define FLOG_PATTERN(FMT) spdlog::set_pattern(FMT)
#define FLOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)

#ifdef FLECTION_NO_LOG
#define FLOG_DEBUG(...)
#define FLOG_INFO(...)
#define FLOG_WARN(...)
#define FLOG_ERROR(...)
#define FLOG_CRITICAL(...)
#else

#define FLOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)

#define FLOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)

#define FLOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)

#define FLOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)

#define FLOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

namespace flection {
class logRegister {
public:
  logRegister();
};

inline flection::logRegister::logRegister() {
  auto defaultLogger = spdlog::stdout_color_mt("m_console_logger");
  spdlog::set_default_logger(defaultLogger);
  FLOG_PATTERN("[MetaParser %H:%M:%S] %v");
}
} // namespace flection

#endif


#endif