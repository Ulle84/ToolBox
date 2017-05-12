// created on 2017-03-01 by Ulrich Belitz

#include <iostream>

#include <QtTest>
#include <QCoreApplication>

#include "Console.h"
#include "CustomTypes.h"

#include "CppHelperTest.h"
#include "QStringExTest.h"
#include "CustomTypesTest.h"
#include "FileTest.h"
#include "PathTest.h"
#include "RingBufferTest.h"
#include "TextTest.h"
#include "ConverterTest.h"

#include "Converter.h"

int main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  QList<QObject*> testObjects;
  testObjects << new CppHelperTest;
  testObjects << new QStringExTest;
  testObjects << new CustomTypesTest;
  testObjects << new FileTest;
  testObjects << new PathTest;
  testObjects << new RingBufferTest;
  testObjects << new TextTest;
  testObjects << new ConverterTest;

  uint32 failedTests = 0;

  for (auto& it : testObjects)
  {
    if (QTest::qExec(it, argc, argv) != 0)
    {
      failedTests++;
    }

    std::cout << std::endl;

    delete it;
  }

  if (failedTests != 0)
  {
    if (failedTests == 1)
    {
      std::string output = Converter::toStdString(failedTests);
      output.append(" test");

      if (failedTests != 1)
      {
        output.append("s");
      }

      output.append(" failed");

      Console::showError(output);
    }
  }
  else
  {
    Console::showSuccess("all tests were successful");
  }

  Console::pressEnterToContinue();

  return failedTests;
}
