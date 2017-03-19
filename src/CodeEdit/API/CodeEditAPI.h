// created on 2017-02-23 by Ulrich Belitz

#ifndef CODEEDITAPI_H
  #define CODEEDITAPI_H

  #ifdef CODEEDIT_EXPORT
    #define CODEEDIT_API __declspec(dllexport)
  #else
    #define CODEEDIT_API __declspec(dllimport)
  #endif

#endif