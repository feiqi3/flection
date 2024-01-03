#pragma once

#include "logWrapper.hpp"
#ifndef LOGWRAPPER_HPP_
#define LOGWRAPPER_HPP_

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <utility>

#define FLOG_PATTERN(FMT) spdlog::set_pattern(FMT)
#define FLOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define FLOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define FLOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define FLOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define FLOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define FLOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

namespace flection {
class logRegist {
public:
  logRegist();
} inline static logRegister;

inline flection::logRegist::logRegist(){
    auto defaultLogger = spdlog::stdout_color_mt("console_logger");
    spdlog::set_default_logger(defaultLogger);
    FLOG_PATTERN("[MetaParser %H:%M:%S] %v");
}
} // namespace flection
#endif