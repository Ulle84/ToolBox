// created on 2017-06-26 by Ulrich Belitz

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT

  public:
    explicit ComboBox(QWidget* parent = 0);

    void setUnit(const QString& unit);

  protected:
    void paintEvent(QPaintEvent* event) override;

    QString m_unit;
};

#endif