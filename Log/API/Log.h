// created on 2017-03-22 by Ulrich Belitz

#ifndef LOG_H
#define LOG_H

#include <QString>

#include "spdlog/logger.h"

#include "LogHelper.h"
#include "LogAPI.h"

class LOG_API Log
{
  public:
    Log(std::string name, bool loggerIsUnique = true);
    ~Log();

    // TODO methods for setting debug level / flush on etc.
    // TODO support for more methods which are implemented in spdlog::logger

    template <typename... Args> inline void trace(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->trace(fmt, args...);
      }
    }

    template <typename... Args> inline void debug(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->debug(fmt, args...);
      }
    }

    template <typename... Args> inline void info(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->info(fmt, args...);
      }
    }

    template <typename... Args> inline void warn(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->warn(fmt, args...);
      }
    }

    template <typename... Args> inline void error(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->error(fmt, args...);
      }
    }

    template <typename... Args> inline void critical(const char* fmt, const Args& ... args)
    {
      if (m_loggingEnabled)
      {
        m_logger->critical(fmt, args...);
      }
    }

    template <typename... Args> inline void flush()
    {
      if (m_loggingEnabled)
      {
        m_logger->flush();
      }
    }

  private:
    std::shared_ptr<spdlog::logger> m_logger = nullptr;    
    bool m_loggingEnabled = false;
};

#endif