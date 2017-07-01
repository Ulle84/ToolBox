// created on 2017-04-14 by Ulrich Belitz

#include "Converter.h"
#include "LogConsole.h"
#include "LogConsoleUi.h"

LogConsole::LogConsole(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::LogConsole)
{
  ui->setupUi(this);
}

LogConsole::~LogConsole()
{
  delete ui;
}

void LogConsole::clear()
{
  ui->plainTextEdit->clear();
}

void LogConsole::warning(const QString& text)
{
  ui->plainTextEdit->appendPlainText(QString("%1 WARNING: %2").arg(currentDateTime()).arg(text));
}

void LogConsole::error(const QString& text)
{
  ui->plainTextEdit->appendPlainText(QString("%1 ERROR:   %2").arg(currentDateTime()).arg(text));
}

void LogConsole::success(const QString& text)
{
  ui->plainTextEdit->appendPlainText(QString("%1 SUCCESS: %2").arg(currentDateTime()).arg(text));
}

void LogConsole::info(const QString& text)
{
  ui->plainTextEdit->appendPlainText(QString("%1 INFO:    %2").arg(currentDateTime()).arg(text));
}

QString LogConsole::currentDateTime()
{
  return Converter::toString(QDateTime::currentDateTime());
}

