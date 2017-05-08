// created on 2017-03-15 by Ulrich Belitz

#ifndef SMLEDITAPI_H
#define SMLEDITAPI_H

#ifdef SMLEDIT_EXPORT
  #define SMLEDIT_API __declspec(dllexport)
#else
  #define SMLEDIT_API __declspec(dllimport)
#endif

#endif