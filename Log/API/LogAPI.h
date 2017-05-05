// created on 2017-03-28 by Ulrich Belitz

#ifndef LOGAPI_H
#define LOGAPI_H

#ifdef LOG_EXPORT
  #define LOG_API __declspec(dllexport)
#else
  #define LOG_API __declspec(dllimport)
#endif

#endif