#ifndef SELECTORDECLARATIONTYPE_H
#define SELECTORDECLARATIONTYPE_H

#include <QWidget>

#include "Class.h"

class SelectorDeclarationTypeUi;

class SelectorDeclarationType : public QWidget
{
    Q_OBJECT

  public:
    explicit SelectorDeclarationType(QWidget* parent = 0);
    ~SelectorDeclarationType();

    Class::DeclarationType declarationType() const;
    bool setDeclarationType(Class::DeclarationType declarationType);

    void setEnabled(bool enabled);

  signals:
    void declarationTypeChanged(int declarationType);

  private slots:
    void on_comboBox_currentIndexChanged(int index);

  private:
    SelectorDeclarationTypeUi* ui;
};

#endif // SELECTORDECLARATIONTYPE_H
