#ifndef SELECTORSINGLETONTYPE_H
#define SELECTORSINGLETONTYPE_H

#include <QWidget>

#include "Class.h"

class SelectorSingletonTypeUi;

class SelectorSingletonType : public QWidget
{
    Q_OBJECT

  public:
    explicit SelectorSingletonType(QWidget* parent = 0);
    ~SelectorSingletonType();

    Class::SingletonType singletonType() const;
    bool setSingletonType(Class::SingletonType singletonType);

    void setEnabled(bool enabled);

  signals:
    void singletonTypeChanged(int dPointerType);

  private slots:
    void on_comboBox_currentIndexChanged(int index);

  private:
    SelectorSingletonTypeUi* ui;
};

#endif // SELECTORSINGLETONTYPE_H
