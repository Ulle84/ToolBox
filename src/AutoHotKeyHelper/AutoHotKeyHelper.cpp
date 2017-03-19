#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QString>

#include "AutoHotKeyHelper.h"

AutoHotKeyHelper::AutoHotKeyHelper()
{
}

void AutoHotKeyHelper::appendToFile(const QString& fileName, const QString& key, const QString& content)
{
  m_keys.clear();

  QFile file(fileName);

  if (!file.exists())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("file does not exist"));
    messageBox.exec();
    return;
  }

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    QMessageBox messageBox;
    messageBox.setText(tr("file could not be openend"));
    messageBox.exec();
    return;
  }

  QTextStream in(&file);
  QString fileContent = in.readAll();
  file.close();

  QStringList lines = fileContent.split('\n');

  extractKeys(lines);

  if (m_keys.contains(key))
  {
    QMessageBox messageBox;
    messageBox.setText(tr("key already included"));
    messageBox.exec();
    return;
  }
  else
  {
    lines.append(QString(":*:%1::%2").arg(key).arg(content));
  }

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return;
  }

  QTextStream out(&file);
  out << lines.join("\n");

  file.close();
}

void AutoHotKeyHelper::parseKeys(const QString& fileName)
{
  m_keys.clear();

  QFile file(fileName);

  if (!file.exists())
  {
    return;
  }

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    return;
  }

  QTextStream in(&file);
  QString fileContent = in.readAll();
  file.close();

  QStringList lines = fileContent.split('\n');

  extractKeys(lines);
}

bool AutoHotKeyHelper::isKeyContained(const QString& key)
{
  return m_keys.contains(key);
}

void AutoHotKeyHelper::extractKeys(const QStringList& lines)
{
  for (auto it = lines.begin(); it != lines.end(); ++it)
  {
    if (it->startsWith(":*:"))
    {
      QString line = it->mid(3);
      QStringList splitted = line.split("::");

      if (splitted.length() == 2)
      {
        QString key = splitted[0];

        if (key.endsWith('#'))
        {
          key = key.left(key.lastIndexOf('#'));
        }

        m_keys.append(key);
      }
    }
  }
}
