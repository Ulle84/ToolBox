#ifndef LISTEDITAPI_H
  #define LISTEDITAPI_H

  #ifdef LISTEDIT_EXPORT
    #define LISTEDIT_API __declspec(dllexport)
  #else
    #define LISTEDIT_API __declspec(dllimport)
  #endif

#endif