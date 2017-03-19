// created on 2016-12-19 by Ulrich Belitz

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
