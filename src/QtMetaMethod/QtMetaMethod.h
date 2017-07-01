#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

class QtMetaMethodUi;

class QtMetaMethod : public QWidget
{
    Q_OBJECT

  public:
    explicit QtMetaMethod(QWidget* parent = 0);
    ~QtMetaMethod();

  public slots:
    void aPublicSlot_Int_String(int i, const QString& string);

  signals:
    void aSignal_Nothing();
    void aSignal_Int_String(int i, const QString& string);

  private slots:
    void aPrivateSlot_Int_String(int i, const QString& string);

  private:
    QtMetaMethodUi* ui;
};

#endif
