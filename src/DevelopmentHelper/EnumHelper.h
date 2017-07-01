#ifndef ENUMHELPER_H
#define ENUMHELPER_H

#include <QWidget>
#include <QStringList>

class EnumHelperUi;

class EnumHelper : public QWidget
{
    Q_OBJECT

  public:
    explicit EnumHelper(QWidget* parent = 0);
    ~EnumHelper();

  private slots:
    void on_pushButtonCreateCodeEnum_clicked();
    void on_pushButtonCreateCodeSwitch_clicked();

  private:
    void updateValues();

    EnumHelperUi* ui;
    QStringList m_values;
};

#endif // ENUMHELPER_H
