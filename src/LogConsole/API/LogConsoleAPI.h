// created on 2017-04-14 by Ulrich Belitz

#ifndef LOGCONSOLEAPI_H
  #define LOGCONSOLEAPI_H

  #ifdef LOGCONSOLE_EXPORT
    #define LOGCONSOLE_API __declspec(dllexport)
  #else
    #define LOGCONSOLE_API __declspec(dllimport)
  #endif

#endif