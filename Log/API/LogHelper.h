// created on 2017-03-22 by Ulrich Belitz

#ifndef LOGHELPER_H
#define LOGHELPER_H

#include "LogAPI.h"
#include "spdlog/logger.h"

namespace spdlog
{
  class logger;
}

namespace LogHelper
{
  std::shared_ptr<spdlog::logger> LOG_API getLogger(const std::string& loggerName, bool loggerIsUnique = true);
  void LOG_API releaseLogger();
}

#endif