// created on 2017-03-25 by Ulrich Belitz

#ifndef PATHSELECTORAPI_H
  #define PATHSELECTORAPI_H

  #ifdef PATHSELECTOR_EXPORT
    #define PATHSELECTOR_API __declspec(dllexport)
  #else
    #define PATHSELECTOR_API __declspec(dllimport)
  #endif

#endif