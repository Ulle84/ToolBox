#ifndef NUMBEREDITAPI_H
#define NUMBEREDITAPI_H

#ifdef NUMBEREDIT_EXPORT
  #define NUMBEREDIT_API __declspec(dllexport)
#else
  #define NUMBEREDIT_API __declspec(dllimport)
#endif

#endif