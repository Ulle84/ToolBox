// created on 2017-01-26 by Ulrich Belitz

#include "Tool.h"

Tool::Tool(const QString& toolName, const QString& inputFileExtension, const QString& outputFileExtension, const QString& outputFilePrefix) :
  m_toolName(toolName),
  m_inputFileExtension(inputFileExtension),
  m_outputFileExtension(outputFileExtension),
  m_outputFilePrefix(outputFilePrefix)
{
}

Tool::~Tool()
{
}

