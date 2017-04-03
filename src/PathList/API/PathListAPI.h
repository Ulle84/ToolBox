// created on 2017-04-01 by Ulrich Belitz

#ifndef PATHLISTAPI_H
  #define PATHLISTAPI_H

  #ifdef PATHLIST_EXPORT
    #define PATHLIST_API __declspec(dllexport)
  #else
    #define PATHLIST_API __declspec(dllimport)
  #endif

#endif