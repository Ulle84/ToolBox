// created on 2017-01-24 by Ulrich Belitz

#include "Arguments.h"

Arguments::Arguments()
{
}

Arguments::Arguments(int argc, char* argv[])
{
  processArguments(argc, argv);
}

Arguments::~Arguments()
{
}

QStringList Arguments::arguments(const QString& name)
{
  return m_arguments[name];
}

bool Arguments::isOptionSet(const QString& name)
{
  return m_arguments.contains(name);
}

void Arguments::clear()
{
  m_arguments.clear();
}

QString Arguments::argument(const QString& name)
{
  QStringList stringList = m_arguments[name];

  if (stringList.isEmpty())
  {
    return QString();
  }
  else
  {
    return stringList.first();
  }
}

void Arguments::processArguments(int argc, char* argv[])
{
  QString currentParameterName;

  for (int i = 1; i < argc; i++)
  {
    QString argument = argv[i];

    if (argument.startsWith('-'))
    {
      currentParameterName = argument;
      m_arguments[currentParameterName] = QStringList();
    }
    else
    {
      m_arguments[currentParameterName].append(argument);
    }
  }
}