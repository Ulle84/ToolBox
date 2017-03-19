// created on 2017-01-23 by Ulrich Belitz

#ifndef CPPHELPERAPI_H
  #define CPPHELPERAPI_H

  #ifdef CPPHELPER_EXPORT
    #define CPPHELPER_API __declspec(dllexport)
  #else
    #define CPPHELPER_API __declspec(dllimport)
  #endif

#endif