// created on 2017-04-14 by Ulrich Belitz

#include "LogConsole.h"
#include "ui_LogConsole.h"

#include "QDateTimeEx.h"

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
	ui->plainTextEdit->appendPlainText(QString("%1 WARNING: %2").arg(QDateTimeEx::currentDateTime()).arg(text));
	
	
	
}

void LogConsole::error(const QString& text)
{
	ui->plainTextEdit->appendPlainText(QString("%1 ERROR:   %2").arg(QDateTimeEx::currentDateTime()).arg(text));
}

void LogConsole::success(const QString& text)
{
	ui->plainTextEdit->appendPlainText(QString("%1 SUCCESS: %2").arg(QDateTimeEx::currentDateTime()).arg(text));
}

void LogConsole::info(const QString& text)
{
	ui->plainTextEdit->appendPlainText(QString("%1 INFO:    %2").arg(QDateTimeEx::currentDateTime()).arg(text));
}


