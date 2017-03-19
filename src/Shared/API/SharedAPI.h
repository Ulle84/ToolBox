// created on 2017-01-11 by Ulrich Belitz

#ifndef SHAREDAPI_H
  #define SHAREDAPI_H

  #ifdef SHARED_EXPORT
    #define SHARED_API __declspec(dllexport)
  #else
    #define SHARED_API __declspec(dllimport)
  #endif

#endif