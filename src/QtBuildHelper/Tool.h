// created on 2017-01-26 by Ulrich Belitz

#ifndef COMMS_TOOL_H
#define COMMS_TOOL_H

#include <QString>

class Tool
{
  public:
    Tool(const QString& toolName, const QString& inputFileExtension, const QString& outputFileExtension, const QString& outputFilePrefix);
    ~Tool();

  public:
    QString m_toolName;
    QString m_inputFileExtension;
    QString m_outputFileExtension;
    QString m_outputFilePrefix;
};

#endif