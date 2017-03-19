// created on 2017-01-04 by Ulrich Belitz

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    return -1;
  }

  QString programPath = argv[1];

  QChar directorySeperator = '\\';
  QStringList tokens = programPath.split(directorySeperator);

  if (tokens.size() < 1)
  {
    return -1;
  }

  QString programName = tokens.last();

  tokens.removeLast();

  QString directory = tokens.join(directorySeperator);

  tokens = programName.split('.');

  if (tokens.last() != "exe")
  {
    return -1;
  }

  tokens.removeLast();

  programName = tokens.last();

  QString src = directory + directorySeperator + "src" + directorySeperator + "build" + directorySeperator + "release" + directorySeperator + "bin" + directorySeperator + programName + ".exe";

  QFile destFile(programPath);
  if (destFile.exists())
  {
    if (!destFile.remove())
    {
      return -1;
    }
  }

  QFile srcFile(src);
  if (!srcFile.copy(programPath))
  {
    return -1;
  }

  return 0;
}
