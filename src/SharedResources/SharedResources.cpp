#include "SharedResources.h"

#include <QTextStream>
#include <QFile>

namespace SharedResources
{
  QString toString(const QString& resource)
  {
    QString fileContent;

    QFile file(resource);

    if (file.exists())
    {
      if (file.open(QFile::ReadOnly | QFile::Text))
      {
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        fileContent = textStream.readAll();
        file.close();
      }
    }

    return fileContent;
  }

  QString defaultStyleSheet()
  {
    return toString(":/files/style.css");
  }

  QString testSmlCode()
  {
    return toString(":/files/test.sml");
  }
}