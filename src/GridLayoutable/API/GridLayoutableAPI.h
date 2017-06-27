// created on 2017-06-27 by Ulrich Belitz

#ifndef GRIDLAYOUTABLEAPI_H
  #define GRIDLAYOUTABLEAPI_H

  #ifdef GRIDLAYOUTABLE_EXPORT
    #define GRIDLAYOUTABLE_API __declspec(dllexport)
  #else
    #define GRIDLAYOUTABLE_API __declspec(dllimport)
  #endif

#endif