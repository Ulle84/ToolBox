#ifndef TEMPLATEAPI_H
  #define TEMPLATEAPI_H

  #ifdef TEMPLATE_EXPORT
    #define TEMPLATE_API __declspec(dllexport)
  #else
    #define TEMPLATE_API __declspec(dllimport)
  #endif

#endif