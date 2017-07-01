// created on 2017-01-26 by Ulrich Belitz

#include "Compiler.h"

Compiler::Compiler(Type type, const QString& name, const QString& inputFileExtension, const QString& outputFileExtension, const QString& outputFileSuffix) :
  m_type(type),
  m_name(name),
  m_inputFileExtension(inputFileExtension),
  m_outputFileExtension(outputFileExtension),
  m_outputFileSuffix(outputFileSuffix)
{
}
