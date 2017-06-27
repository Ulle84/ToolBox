// created on 2017-06-27 by Ulrich Belitz

#ifndef GRIDLAYOUTABLESCONNECTOR_H
#define GRIDLAYOUTABLESCONNECTOR_H

#include <QObject>
#include <QSet>

class GridLayoutable;

class GridLayoutablesConnector : public QObject
{
    Q_OBJECT

  public:
    explicit GridLayoutablesConnector(QObject* parent = 0);
    ~GridLayoutablesConnector();

    void addGridLayoutable(GridLayoutable* gridLayoutable);
    bool removeGridLayoutable(GridLayoutable* gridLayoutable);

    void updateWidths();

  private:
    QSet<GridLayoutable*> m_gridLayoutables;
};

#endif