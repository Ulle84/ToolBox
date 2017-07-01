#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaType>
#include <QStringList>

#include "QtMetaMethod.h"
#include "QtMetaMethodUi.h"

QtMetaMethod::QtMetaMethod(QWidget* parent) :
  QWidget(parent),
  ui(new QtMetaMethodUi)
{
  ui->setupUi(this);

  const QMetaObject* metaObject = this->metaObject();

  QStringList slotSignatures;
  QStringList signalSignatures;

  for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
  {
    QMetaMethod metaMethod = metaObject->method(i);

    if (metaMethod.methodType() == QMetaMethod::Signal)
    {
      signalSignatures.append(QString(metaMethod.methodSignature()));
    }
    else if (metaMethod.methodType() == QMetaMethod::Slot)
    {
      slotSignatures.append(QString(metaMethod.methodSignature()));
    }
  }

  ui->plainTextEdit->appendPlainText("slots:");
  ui->plainTextEdit->appendPlainText(slotSignatures.join('\n'));

  ui->plainTextEdit->appendPlainText("\nsignals:");
  ui->plainTextEdit->appendPlainText(signalSignatures.join('\n'));
}

QtMetaMethod::~QtMetaMethod()
{
  delete ui;
}

void QtMetaMethod::aPrivateSlot_Int_String(int i, const QString& string)
{
}

void QtMetaMethod::aPublicSlot_Int_String(int i, const QString& string)
{
}
