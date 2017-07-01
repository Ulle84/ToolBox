#include "Widget.h"
#include "WidgetUi.h"

Widget::Widget(QWidget* parent) :
  QWidget(parent),
  ui(new WidgetUi)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::setNewParameter(const QString& name, const QString& value)
{
  ui->plainTextEdit->appendPlainText(QString("%1: %2").arg(name).arg(value));
}

void Widget::setNewGeneratedNumber(int newNumber)
{
  ui->plainTextEdit->appendPlainText(QString("new generated number: %1").arg(newNumber));
}

void Widget::on_pushButton_clicked()
{
  emit parameterChanged(ui->lineEditParameter->text(), ui->lineEditValue->text());
}