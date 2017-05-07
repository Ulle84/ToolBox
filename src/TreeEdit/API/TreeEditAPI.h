// created on 2017-03-06 by Ulrich Belitz

#ifndef TREEEDITAPI_H
#define TREEEDITAPI_H

#ifdef TREEEDIT_EXPORT
  #define TREEEDIT_API __declspec(dllexport)
#else
  #define TREEEDIT_API __declspec(dllimport)
#endif

#endif