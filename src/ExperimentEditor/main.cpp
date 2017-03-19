// created on 2017-01-25 by Ulrich Belitz

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
