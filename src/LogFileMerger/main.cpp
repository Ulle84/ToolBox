// created on 2017-03-23 by Ulrich Belitz

#include <QProcess>
#include <QString>
#include <QStringList>

#include "File.h"
#include "Console.h"

const int dateTimeLength = 23;

bool lessThan(const QString& s1, const QString& s2)
{
  return s1.left(dateTimeLength).toLower() < s2.left(dateTimeLength).toLower();
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

  while (!merged.isEmpty())
  {
    if (merged.first().length() < dateTimeLength)
    {
      merged.removeFirst();
    }
    else
    {
      break;
    }
  }

  QString firstFileName = fileNames.first();

  int startPosition = firstFileName.lastIndexOf('_');
  int endPosition = firstFileName.lastIndexOf('.');

  QString fileName = firstFileName.remove(startPosition, endPosition - startPosition);

  File::stringListToFile(merged, fileName);

  QString program = "D:\\Programs\\Portable\\Notepad++\\Notepad++.exe";

  QProcess::startDetached(program, QStringList() << fileName);

  return 0;
}
