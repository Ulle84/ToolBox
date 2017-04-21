// created on 2017-04-15 by Ulrich Belitz

#ifndef GRIDLAYOUTERAPI_H
  #define GRIDLAYOUTERAPI_H

  #ifdef GRIDLAYOUTER_EXPORT
    #define GRIDLAYOUTER_API __declspec(dllexport)
  #else
    #define GRIDLAYOUTER_API __declspec(dllimport)
  #endif

#endif