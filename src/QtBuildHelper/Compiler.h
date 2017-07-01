// created on 2017-01-26 by Ulrich Belitz

#ifndef COMPILER_H
#define COMPILER_H

#include <QString>

class Compiler
{
  public:
    enum class Type
    {
      MetaObject,
      UserInterface,
      Resources,
      Replica,
      Source
    };

    Compiler(Type type, const QString& name, const QString& inputFileExtension, const QString& outputFileExtension, const QString& outputFileSuffix);

    Type m_type;
    QString m_name;
    QString m_inputFileExtension;
    QString m_outputFileExtension;
    QString m_outputFileSuffix;
};

#endif