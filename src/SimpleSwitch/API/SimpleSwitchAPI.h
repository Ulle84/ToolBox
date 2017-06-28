// created on 2017-06-28 by Ulrich Belitz

#ifndef SIMPLESWITCHAPI_H
  #define SIMPLESWITCHAPI_H

  #ifdef SIMPLESWITCH_EXPORT
    #define SIMPLESWITCH_API __declspec(dllexport)
  #else
    #define SIMPLESWITCH_API __declspec(dllimport)
  #endif

#endif