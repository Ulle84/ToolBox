// created on 2017-06-27 by Ulrich Belitz

#include <QMessageBox>

#include "GridLayoutablesConnector.h"
#include "GridLayoutable.h"

GridLayoutablesConnector::GridLayoutablesConnector(QObject* parent) :
  QObject(parent)
{
}

GridLayoutablesConnector::~GridLayoutablesConnector()
{
  for (auto it = m_gridLayoutables.begin(); it != m_gridLayoutables.end(); ++it)
  {
    (*it)->invalidateConnector();
  }
}

void GridLayoutablesConnector::addGridLayoutable(GridLayoutable* gridLayoutable)
{
  m_gridLayoutables.insert(gridLayoutable);
  updateWidths();
}

bool GridLayoutablesConnector::removeGridLayoutable(GridLayoutable* gridLayoutable)
{
  bool success = m_gridLayoutables.remove(gridLayoutable);

  if (success)
  {
    //QMessageBox mb;
    //mb.setText("removed - update");
    //mb.exec();

    updateWidths();
  }

  return success;
}

void GridLayoutablesConnector::updateWidths()
{
  QVector<int> minimumWidths;

  for (auto it = m_gridLayoutables.begin(); it != m_gridLayoutables.end(); ++it)
  {
    if (!(*it)->isGridLayouted())
    {
      continue;
    }

    QVector<int> vec = (*it)->minimumWidths();

    for (int i = 0; i < vec.length(); ++i)
    {
      if (i >= minimumWidths.length())
      {
        minimumWidths.resize(i + 1);
      }

      if (vec[i] > minimumWidths[i])
      {
        minimumWidths[i] = vec[i];
      }
    }
  }

  for (auto it = m_gridLayoutables.begin(); it != m_gridLayoutables.end(); ++it)
  {
    if ((*it)->isGridLayouted())
    {
      (*it)->setMinimumWidths(minimumWidths);
    }
  }
}
