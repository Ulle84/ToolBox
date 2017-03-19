#ifndef AUTOHOTKEYHELPER_H
#define AUTOHOTKEYHELPER_H

#include <QObject>
#include <QString>
#include <QStringList>

class AutoHotKeyHelper : public QObject
{
    Q_OBJECT

  public:
    AutoHotKeyHelper();

    void appendToFile(const QString& fileName, const QString& key, const QString& content);
    void parseKeys(const QString& fileName);
    bool isKeyContained(const QString& key);

  private:
    void extractKeys(const QStringList& lines);

    QStringList m_keys;
};

#endif // AUTOHOTKEYHELPER_H