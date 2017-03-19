// created on 2016-10-26

#ifndef StringHandler_h
#define StringHandler_h

#include <QString>
#include <QChar>
#include <QStringList>

class StringHandler
{
  public:
    StringHandler();

    void parseAndReplaceStrings(QString& code);
    void revertStrings(QString& code);

  private:
    int nextTokenIndex(const QString& code, int startIndex);
    bool isIndexValid(int index);

    const QChar m_token = '\"';
    const QString m_replacementMask = "\"###%1###\"";
    QStringList m_strings;
};

#endif