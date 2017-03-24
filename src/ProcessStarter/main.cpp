#include <QCoreApplication>
#include <QProcess>

#include "Path.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  if (argc > 1)
  {
    QString program = Path::portableProgram("Notepad++");

    QString fileName = argv[1];
    int pointPos = fileName.lastIndexOf('.');    

    if (pointPos > -1)
    {
      QString fileExtension = fileName.mid(pointPos + 1);

      if (fileExtension == "png")
      {
        program = Path::portableProgram("Greenshot");
      }
    }

    QProcess::startDetached(program, QStringList() << fileName);
  }
}
