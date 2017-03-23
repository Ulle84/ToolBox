// created on 2017-03-23 by Ulrich Belitz

#include <QString>
#include <QStringList>

#include "File.h"
#include "Console.h"

bool lessThan(const QString& s1, const QString& s2)
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

  QString firstFileName = fileNames.first();

  int startPosition = firstFileName.lastIndexOf('_');
  int endPosition = firstFileName.lastIndexOf('.');

  QString fileName = firstFileName.remove(startPosition, endPosition - startPosition);

  File::stringListToFile(merged, fileName);

  return 0;
}
