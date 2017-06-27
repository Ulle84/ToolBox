#include <QVariant>
#include <QEvent>
#include <QMessageBox> // TODO remove this line after testing


#include "GridLayoutable.h"
#include "GridLayoutablesConnector.h"

GridLayoutable::GridLayoutable(QWidget* parent) :
  QWidget(parent)
{
  addToConnector();
}

GridLayoutable::~GridLayoutable()
{
  removeFromConnector();

  //m_master = false;
  //
  //QObject* object = parent();
  //GridLayoutable* master = nullptr;

  // TODO transfer mastership to another object - connect signals and slots

  //if (object)
  //{
  //  QList<GridLayoutable*> gridLayoutables = object->findChildren<GridLayoutable*>(QString(), Qt::FindDirectChildrenOnly);
  //
  //  for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
  //  {
  //    if (*it != this)
  //    {
  //      master = *it;
  //    }
  //
  //    if (master)
  //    {
  //      connect(master, &GridLayoutable::minimumWidthsChanged, *it, &GridLayoutable::onMinimumWidthsChanged);
  //    }
  //  }
  //
  //  //if (master)
  //  //  master->setMaster(true);
  //}

  //if (object && m_eventFilterInstalled)
  //{
  //  object->setProperty(m_propertyName, false);
  //  object->removeEventFilter(this);
  //
  //  //transfer event filter to next GridLayoutable, if existing
  //  QList<GridLayoutable*> gridLayoutables = object->findChildren<GridLayoutable*>(QString(), Qt::FindDirectChildrenOnly);
  //
  //  for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
  //  {
  //    if (*it != this)
  //    {
  //      (*it)->installEventFilter();
  //      break;
  //    }
  //  }
  //}
}

void GridLayoutable::setGridLayouted(bool gridLayouted)
{
  m_gridLayouted = gridLayouted;

  if (!gridLayouted)
  {
    resetMinumumWidths();
  }
  else
  {
    m_gridLayoutablesConnector->updateWidths();
    //    emit minimumWidthsChanged();
  }
}

bool GridLayoutable::isGridLayouted()
{
  return m_gridLayouted;
}

void GridLayoutable::invalidateConnector()
{
  m_gridLayoutablesConnector = nullptr;
}

void GridLayoutable::updateWidths()
{
  if (m_gridLayoutablesConnector)
    m_gridLayoutablesConnector->updateWidths();
}

void GridLayoutable::addToConnector()
{
  //installEventFilter();
  QObject* object = this->parent();
  //
  //if (object)
  //{
  //  QList<GridLayoutable*> gridLayoutables = object->findChildren<GridLayoutable*>(QString(), Qt::FindDirectChildrenOnly);
  //
  //  if (gridLayoutables.size() == 1)
  //  {
  //    m_master = true;
  //  }
  //
  //  for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
  //  {
  //    if ((*it)->isMaster())
  //    {
  //      bool success = connect(this, &GridLayoutable::minimumWidthsChanged, *it, &GridLayoutable::onMinimumWidthsChanged);
  //      int test = rand();
  //    }
  //  }
  //}

  if (object)
  {
    QList<GridLayoutablesConnector*> list = object->findChildren<GridLayoutablesConnector*>(QString(), Qt::FindDirectChildrenOnly);

    if (list.isEmpty())
    {
      m_gridLayoutablesConnector = new GridLayoutablesConnector(object);
    }
    else
    {
      m_gridLayoutablesConnector = list.first();
    }

    m_gridLayoutablesConnector->addGridLayoutable(this);
  }
}

void GridLayoutable::removeFromConnector()
{
  if (m_gridLayoutablesConnector)
  {
    m_gridLayoutablesConnector->removeGridLayoutable(this);    
  }
}

bool GridLayoutable::event(QEvent* event)
{
  if (event->type() == QEvent::ParentAboutToChange)
  {
    removeFromConnector();
  }
  else if (event->type() == QEvent::ParentChange)
  {
    addToConnector();
  }

  return QWidget::event(event);
}

//void GridLayoutable::setMaster(bool master)
//{
//  m_master = master;
//
//  if (m_master)
//    onMinimumWidthsChanged();
//}
//
//bool GridLayoutable::isMaster()
//{
//  return m_master;
//}

//void GridLayoutable::onMinimumWidthsChanged()
//{
//  QList<GridLayoutable*> gridLayoutables = parent()->findChildren<GridLayoutable*>(QString(), Qt::FindDirectChildrenOnly);
//
//  QVector<int> minimumWidths;
//
//  for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
//  {
//    if (!(*it)->isGridLayouted())
//    {
//      continue;
//    }
//
//    QVector<int> vec = (*it)->minimumWidths();
//
//    for (int i = 0; i < vec.length(); ++i)
//    {
//      if (i >= minimumWidths.length())
//      {
//        minimumWidths.resize(i + 1);
//      }
//
//      if (vec[i] > minimumWidths[i])
//      {
//        minimumWidths[i] = vec[i];
//      }
//    }
//  }
//
//  for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
//  {
//    if ((*it)->isGridLayouted())
//    {
//      (*it)->setMinimumWidths(minimumWidths);
//    }
//  }
//}

//void GridLayoutable::installEventFilter()
//{
//  QObject* object = parent();
//
//  if (object)
//  {
//    if (!(object->property(m_propertyName).isValid() && object->property(m_propertyName).toBool()))
//    {
//      m_eventFilterInstalled = true;
//      object->installEventFilter(this);
//      object->setProperty(m_propertyName, true);
//    }
//  }
//}

//bool GridLayoutable::eventFilter(QObject* watched, QEvent* event)
//{
//  if (event->type() == QEvent::Paint)
//  {
//
//
//    QList<GridLayoutable*> gridLayoutables = parent()->findChildren<GridLayoutable*>(QString(), Qt::FindDirectChildrenOnly);
//
//    for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
//    {
//      if ((*it)->isGridLayouted())
//      {
//        (*it)->resetMinumumWidths();
//      }
//    }
//
//    bool result = watched->event(event);
//
//    QVector<int> minimumWidths;
//
//    for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
//    {
//      if (!(*it)->isGridLayouted())
//      {
//        continue;
//      }
//
//      QVector<int> vec = (*it)->minimumWidths();
//
//      for (int i = 0; i < vec.length(); ++i)
//      {
//        if (i >= minimumWidths.length())
//        {
//          minimumWidths.resize(i + 1);
//        }
//
//        if (vec[i] > minimumWidths[i])
//        {
//          minimumWidths[i] = vec[i];
//        }
//      }
//    }
//
//    for (auto it = gridLayoutables.begin(); it != gridLayoutables.end(); ++it)
//    {
//      if ((*it)->isGridLayouted())
//      {
//        (*it)->setMinimumWidths(minimumWidths);
//      }
//    }
//
//    return result;
//  }
//
//  return QWidget::eventFilter(watched, event);
//}