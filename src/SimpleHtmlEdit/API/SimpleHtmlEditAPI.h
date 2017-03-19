// created on 2017-03-15 by Ulrich Belitz

#ifndef SIMPLEHTMLEDITAPI_H
#define SIMPLEHTMLEDITAPI_H

#ifdef SIMPLEHTMLEDIT_EXPORT
  #define SIMPLEHTMLEDIT_API __declspec(dllexport)
#else
  #define SIMPLEHTMLEDIT_API __declspec(dllimport)
#endif

#endif