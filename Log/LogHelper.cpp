// created on 2017-03-22 by Ulrich Belitz

#include <string>

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QString>

#include "Base.h"
#include "Log.h"

#include "spdlog/spdlog.h"

namespace LogHelper
{
  volatile bool loggingEnabled = false;
  volatile bool settingsApplied = false;
  int nLoggers = 0;
  QDateTime dateTime = QDateTime::currentDateTime();
  QMutex mutex;
  QMap<std::string, int> loggerIds;
  QMap<std::string, std::shared_ptr<spdlog::sinks::simple_file_sink_mt>> fileSinks;

  // TODO release logger function - if the last logger is released the spdlog API can be released -> spdlog::drop_all();

  std::shared_ptr<spdlog::logger> getLogger(const std::string& loggerName, bool loggerIsUnique)
  {
    // TODO Test
    // TODO Refactoring


    QMutexLocker locker(&mutex);

    ++nLoggers;

    if (!settingsApplied)
    {
      loggingEnabled = Base::Configuration::getInstance().getBoolValue(L"Debug.LoggingEnabled", false);

      spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %L %t %n %v"); // documentation: see comment at end of this file
      settingsApplied = true;
    }

    if (!loggingEnabled)
    {
      return nullptr;
    }

    QString loggerFileName;

    if (loggerIsUnique)
    {
      if (!loggerIds.contains(loggerName))
      {
        loggerIds[loggerName] = 0;
      }
      else
      {
        ++loggerIds[loggerName];
      }

      loggerFileName = QString::fromStdString(loggerName) + "-" + QString::number(loggerIds[loggerName]);
    }
    else
    {
      // TODO get logger with shared file sink - see comment below
      // TODO test loggers with shared file sink
      loggerFileName = QString::fromStdString(loggerName);
    }

    QString dateTimeString = dateTime.toString("yyyy-MM-dd_hh-mm-ss");

    std::string appPath = QCoreApplication::applicationDirPath().toStdString();

    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    dir.mkdir("log");
    dir.cd("log");
    dir.mkdir(dateTimeString);

    QString fileName = dir.absolutePath();
    fileName.append("/");
    fileName.append(dateTimeString);
    fileName.append("/");
    fileName.append(dateTimeString);
    fileName.append("_");
    fileName.append(loggerFileName);
    fileName.append(".log");

    std::shared_ptr<spdlog::logger> logger;

    if (loggerIsUnique)
    {
      logger = spdlog::basic_logger_mt(loggerName + " " + std::to_string(loggerIds[loggerName]), fileName.toStdString());
    }
    else
    {
      if (!fileSinks.contains(loggerName))
      {
        fileSinks[loggerName] = std::make_shared<spdlog::sinks::simple_file_sink_mt>(fileName.toStdString());
      }

      logger = std::make_shared<spdlog::logger>(loggerName, fileSinks[loggerName]);
    }

    // TODO make these two parameters configurable?
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::err);

    return logger;
  }

  void releaseLogger()
  {
    QMutexLocker locker(&mutex);
    --nLoggers;

    if (loggingEnabled)
    {
      if (nLoggers == 0)
      {
        spdlog::drop_all();
      }        
    }    
  }
}

/* spdlog::set_pattern

%v  The actual text to log  "some user text"
%t  Thread id   "1232"
%P  Process id  "3456"
%n  Logger's name   "some logger name"
%l  The log level of the message  "debug", "info", etc
%L  Short log level of the message  "D", "I", etc
%a  Abbreviated weekday name  "Thu"
%A  Full weekday name   "Thursday"
%b  Abbreviated month name  "Aug"
%B  Full month name   "August"
%c  Date and time representation  "Thu Aug 23 15:35:46 2014"
%C  Year in 2 digits  "14"
%Y  Year in 4 digits  "2014"
%D or %x  Short MM/DD/YY date   "08/23/14"
%m  Month 1-12  "11"
%d  Day of month 1-31   "29"
%H  Hours in 24 format 0-23   "23"
%I  Hours in 12 format 1-12   "11"
%M  Minutes 0-59  "59"
%S  Seconds 0-59  "58"
%e  Millisecond part of the current second 0-999  "678"
%f  Microsecond part of the current second 0-999999   "056789"
%F  Nanosecond part of the current second 0-999999999   "256789123"
%p  AM/PM   "AM"
%r  12 hour clock   "02:55:02 pm"
%R  24-hour HH:MM time, equivalent to %H:%M   "23:55"
%T or %X  ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S   "23:55:59"
%z  ISO 8601 offset from UTC in timezone ([+/-]HH:MM)   "+02:00"
%%  The % sign  "%"
%+  spdlog's default format   "[2014-31-10 23:46:59.678] [mylogger] [info] Some message"

*/