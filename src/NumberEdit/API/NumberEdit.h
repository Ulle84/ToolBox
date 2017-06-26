#ifndef NUMBEREDIT_H
#define NUMBEREDIT_H

#include <QWidget>

#include "Gridable.h"
#include "NumberEditAPI.h"

namespace Ui
{
  class NumberEdit;
}

class NUMBEREDIT_API NumberEdit : public Gridable
{
    Q_OBJECT

      Q_PROPERTY(QString label READ label WRITE setLabel)
      Q_PROPERTY(QString unit READ unit WRITE setUnit)

  public:
    explicit NumberEdit(QWidget* parent = 0);
    ~NumberEdit();

    // Gridable
    QVector<int> minimumWidths() override;
    void setMinimumWidths(const QVector<int>& minimumWidths) override;
    void resetMinimumWidths() override;

    void setLabel(const QString& label);
    QString label();

    void setUnit(const QString& unit);
    QString unit();

  protected:
    // TODO move eventFilter stuff into BaseClass Gridable?
    bool eventFilter(QObject * watched, QEvent * event) override;

  private:
    Ui::NumberEdit* ui;

    bool gridableEventFilterInstalledByThisInstance = false;
};

#endif
