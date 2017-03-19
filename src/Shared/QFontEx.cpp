// created on 2017-02-23 by Ulrich Belitz

#include "QFontEx.h"

QFont QFontEx::monospace()
{
  #ifdef Q_OS_MAC
  return QFont("Monaco", 12);
  #else
  return QFont("Courier New", 10);
  #endif
}
