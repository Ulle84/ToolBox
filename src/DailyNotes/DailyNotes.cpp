#include <QDebug>

#include "DailyNotes.h"
#include "ui_DailyNotes.h"

#include "SimpleHtmlConverter.h"
#include "Path.h"
#include "File.h"
#include "Converter.h"

DailyNotes::DailyNotes(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DailyNotes)
{
  ui->setupUi(this);
  ui->codeEdit->setCodeHighlightingType(CodeEdit::CodeHighlightingType::SimpleHtml);

  ui->calendarWidget->setSelectedDate(QDate::currentDate());
  update(QDate::currentDate());
}

DailyNotes::~DailyNotes()
{
  saveCurrent();
  delete ui;
}

void DailyNotes::on_codeEdit_textChanged()
{
  SimpleHtmlConverter simpleHtmlConverter;
  ui->webView->setHtml(simpleHtmlConverter.toHtml(ui->codeEdit->toPlainText()));
}

void DailyNotes::on_calendarWidget_activated(const QDate& date)
{
  update(date);
}

void DailyNotes::on_calendarWidget_clicked(const QDate& date)
{
  update(date);
}

QString DailyNotes::path(const QDate& date)
{
  QStringList stringList;

  stringList << Path::content();
  stringList << "DailyNotes";
  stringList << QString::number(date.year());
  stringList << QString("%1.shtml").arg(date.toString("yyyy-MM-dd"));

  return Converter::toPath(stringList);
}


void DailyNotes::update(const QDate& date)
{
  saveCurrent();

  ui->codeEdit->setPlainText(File::fileToString(path(date)));

  m_selectedDate = date;
}

void DailyNotes::saveCurrent()
{
  if (m_selectedDate.isValid())
  {
    // TODO if text is empty a emtpy file is written
    File::stringToFile(ui->codeEdit->toPlainText(), path(m_selectedDate));
  }
}
