// created on 2017-03-22 by Ulrich Belitz

#include "Log.h"

Log::Log(std::string name, bool loggerIsUnique)
{
  m_logger = LogHelper::getLogger(name, loggerIsUnique);
  if (m_logger)
    m_loggingEnabled = true;
}

Log::~Log()
{
  if (m_logger)
  {
    m_logger->flush();
  }
  
  LogHelper::releaseLogger();
}