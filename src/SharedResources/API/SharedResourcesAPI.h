#ifndef SHAREDRESOURCESAPI_H
  #define SHAREDRESOURCESAPI_H

  #ifdef SHAREDRESOURCES_EXPORT
    #define SHAREDRESOURCES_API __declspec(dllexport)
  #else
    #define SHAREDRESOURCES_API __declspec(dllimport)
  #endif

#endif