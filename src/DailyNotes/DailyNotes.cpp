#include <QDebug>
#include <QFile>

#include "DailyNotes.h"
#include "ui_DailyNotes.h"

#include "SmlConverter.h"
#include "Path.h"
#include "File.h"
#include "Converter.h"

DailyNotes::DailyNotes(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DailyNotes)
{
  ui->setupUi(this);
  ui->codeEdit->setCodeHighlightingType(CodeEdit::CodeHighlightingType::Sml);

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
  SmlConverter smlConverter;
  ui->webView->setHtml(smlConverter.toHtml(ui->codeEdit->toPlainText()));
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

void DailyNotes::setDate(const QDate& date)
{
  ui->calendarWidget->setSelectedDate(date);
  update(date);
}

void DailyNotes::on_pushButtonToday_clicked()
{
  setDate(QDate::currentDate());
}

void DailyNotes::on_pushButtonOneDayForward_clicked()
{
  setDate(m_selectedDate.addDays(1));
}

void DailyNotes::on_pushButtonOneDayBackward_clicked()
{
  setDate(m_selectedDate.addDays(-1));
}

void DailyNotes::on_pushButtonOneMonthForward_clicked()
{
  setDate(m_selectedDate.addMonths(1));
}

void DailyNotes::on_pushButtonOneMonthBackward_clicked()
{
  setDate(m_selectedDate.addMonths(-1));
}

void DailyNotes::on_pushButtonOneYearForward_clicked()
{
  setDate(m_selectedDate.addYears(1));
}

void DailyNotes::on_pushButtonOneYearBackward_clicked()
{
  setDate(m_selectedDate.addYears(-1));
}

void DailyNotes::saveCurrent()
{
  if (m_selectedDate.isValid())
  {
    QString content = ui->codeEdit->toPlainText();

    if (content.isEmpty())
    {
      QFile::remove(path(m_selectedDate));
    }
    else
    {
      File::stringToFile(content, path(m_selectedDate));
    }
  }
}
