#include <QDebug>
#include <QCoreApplication>

int main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  qDebug() << "starting event loop";

  return a.exec();
}
