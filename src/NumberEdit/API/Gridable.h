#ifndef GRIDABLE_H
#define GRIDABLE_H

#include <QVector>
#include <QWidget>

class Gridable : public QWidget
{
public:
  explicit Gridable(QWidget* parent = 0);

  virtual QVector<int> minimumWidths() = 0;
  virtual void setMinimumWidths(const QVector<int>& minimumWidths) = 0;
  virtual void resetMinimumWidths() = 0;

};

#endif