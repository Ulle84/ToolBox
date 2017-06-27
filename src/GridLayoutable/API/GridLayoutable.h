#ifndef GRIDLAYOUTABLE_H
#define GRIDLAYOUTABLE_H

#include <QVector>
#include <QWidget>

#include "GridLayoutableAPI.h"

class GridLayoutablesConnector;

class GRIDLAYOUTABLE_API GridLayoutable : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool gridLayouted READ isGridLayouted WRITE setGridLayouted)

  public:
    explicit GridLayoutable(QWidget* parent = 0);
    ~GridLayoutable();

    virtual QVector<int> minimumWidths() = 0;
    virtual void setMinimumWidths(const QVector<int>& widths) = 0;
    virtual void resetMinumumWidths() = 0;

    virtual void setGridLayouted(bool gridLayouted);
    bool isGridLayouted();

    void invalidateConnector();

    void updateWidths();

    //signals:
    //  void minimumWidthsChanged();
    //
    //public slots:
    //  void onMinimumWidthsChanged();

    //protected:
    //  void setMaster(bool master);
    //  bool isMaster();

    //void installEventFilter();

    //protected:
    //  bool eventFilter(QObject* watched, QEvent* event) override;

  protected:
    bool event(QEvent* event) override;

    

  private:
    void addToConnector();
    void removeFromConnector();

    //const char* m_propertyName = "gridLayoutableEventFilterInstalled"; // memory leak? delete?
    //bool m_eventFilterInstalled = false;
    //bool m_master = false;
    bool m_gridLayouted = false;
    GridLayoutablesConnector* m_gridLayoutablesConnector = nullptr;
};

#endif