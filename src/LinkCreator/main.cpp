// created on 2017-01-06 by Ulrich Belitz

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFile>

#include "MainWindow.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    qDebug() << "ERROR: you need to provide a command line argument!";
    return -1;
  }

  QString input = argv[1];
  QFile file(input);

  if (!file.exists())
  {
    qDebug() << "ERROR: directory does not exist!";
    return -1;
  }

  QApplication a(argc, argv);
  MainWindow w(input);
  w.show();

  return a.exec();
}
