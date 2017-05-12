#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "File.h"
#include "Path.h"
#include "QStringEx.h"

File::File(const QString& path) :
  m_path(path)
{
}

File::~File()
{
}

QString File::toString()
{
  QString fileContent;

  QFile file(m_path);

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

QStringList File::toStringList()
{
  return toString().split("\n");
}

QStringMap File::toStringMap()
{
  QMap<QString, QString> map;

  QStringList stringList = toStringList();

  for (auto it : stringList)
  {
    QStringList splitted = it.split(m_mapSeperator, QString::KeepEmptyParts);

    if (splitted.length() != 2)
    {
      continue;
    }

    map[splitted[0]] = splitted[1];
  }

  return map;
}

bool File::write(const QString& string)
{
  QFile file(m_path);

  if (file.open(QIODevice::WriteOnly | QFile::Text))
  {
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    textStream << string;

    file.close();
    return true;
  }
  else
  {
    return false;
  }
}

bool File::write(const QStringList& stringList)
{
  return write(stringList.join("\n"));
}

bool File::write(const QStringMap& stringMap)
{
  QStringList stringList;

  for (auto it = stringMap.begin(); it != stringMap.end(); ++it)
  {
    stringList.append(QString("%1%2%3").arg(it.key()).arg(m_mapSeperator).arg(it.value()));
  }

  return write(stringList);
}

void File::setMapSeperator(const QString& mapSeperator)
{
  m_mapSeperator = mapSeperator;
}

QString File::directory()
{
  int max = std::max(m_path.lastIndexOf('/'), m_path.lastIndexOf('\\'));

  if (max == -1)
  {
    return QString();
  }

  return m_path.left(max);
}

QString File::checkSum()
{
  QFile file(m_path);

  if (file.open(QFile::ReadOnly))
  {
    QCryptographicHash hash(QCryptographicHash::Md5);

    if (hash.addData(&file))
    {
      QString string(hash.result().toBase64());
      QStringEx::removeTrailingSigns(string, '=');
      return string;
    }
  }

  return QString();
}

QString File::name()
{
  QStringList splitted = Path::split(m_path);

  if (splitted.isEmpty())
  {
    return QString();
  }

  return splitted.last();
}
