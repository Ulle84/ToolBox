// created on 2017-03-23 by Ulrich Belitz

#include <QString>
#include <QStringList>

#include "File.h"
#include "Console.h"

bool lessThan(const QString &s1, const QString &s2)
{
  int length = 23;
  return s1.left(length).toLower() < s2.left(length).toLower();
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    return 1;
  }

  QStringList fileNames;

  for (int i = 1; i < argc; ++i)
  {
    fileNames.append(QString(argv[i]));
  }

  QStringList merged = File::merge(fileNames);

  qStableSort(merged.begin(), merged.end(), lessThan);

  //QString fileName = fileNames.first().left(19) + ".txt";
  QString firstFileName = fileNames.first();

  Console::showInfo(firstFileName.toStdString());

  int startPosition = firstFileName.lastIndexOf('_');
  int endPosition = firstFileName.lastIndexOf('.');

  Console::showValue("startPosition", startPosition);
  Console::showValue("endPosition", endPosition);

  QString fileName = firstFileName.remove(startPosition, endPosition - startPosition);

  Console::showInfo(fileName.toStdString());

  File::stringListToFile(merged, fileName);

  Console::pressEnterToContinue();

  return 0;
}
