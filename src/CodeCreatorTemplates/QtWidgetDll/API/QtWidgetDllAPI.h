#ifndef QTWIDGETDLLAPI_H
  #define QTWIDGETDLLAPI_H

  #ifdef QTWIDGETDLL_EXPORT
    #define QTWIDGETDLL_API __declspec(dllexport)
  #else
    #define QTWIDGETDLL_API __declspec(dllimport)
  #endif

#endif