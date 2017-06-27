// created on 2017-06-20 by Ulrich Belitz

#ifndef NUMBEREDIT_H
#define NUMBEREDIT_H

#include <QWidget>
#include <QString>

#include "GridLayoutable.h"
#include "NumberEditAPI.h"

namespace Ui
{
  class NumberEdit;
}

class NUMBEREDIT_API NumberEdit : public GridLayoutable
{
    Q_OBJECT

    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(QString unit READ unit WRITE setUnit)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double warningFactor READ warningFactor WRITE setWarningFactor)
    Q_PROPERTY(int unitWidth READ unitWidth WRITE setUnitWidth)

  public:
    explicit NumberEdit(QWidget* parent = 0);
    ~NumberEdit();

    void setLabel(const QString& label);
    QString label();

    void setUnit(const QString& unit);
    QString unit();

    void setValue(double value);
    double value();

    int toInt();
    double toDouble();

    void setMinimum(double minimum);
    double minimum();

    void setMaximum(double maximum);
    double maximum();

    void setRange(double minimum, double maximum);

    void setDecimals(int decimals);
    int decimals();

    void setWarningFactor(double warningFactor);
    double warningFactor();

    void setUnitWidth(int unitWidth);
    int unitWidth();

    // GridLayoutable interface
    QVector<int> minimumWidths() override;
    void setMinimumWidths(const QVector<int>& widths) override;
    void resetMinumumWidths() override;

  private slots:
    void on_doubleSpinBox_valueChanged(double value);
    void on_comboBox_currentIndexChanged(int index);

  private:
    void setupUnitSelector();
    void updateControl();
    void applyWarningFactor();

    void updateLabelDisplay(int width);
    void updateUnitDisplay(int width);

    Ui::NumberEdit* ui;
    QString m_unit;
    double m_value = 0.0;

    double m_minimum;
    double m_maximum;

    double m_warningFactor = 0.0;

    const int m_maxExponent = 13; // the highest used potency + 1

    double m_supportedMin;
    double m_supportedMax;

    int m_labelWidth = 0;
    int m_unitWidth = 50;
};

#endif
