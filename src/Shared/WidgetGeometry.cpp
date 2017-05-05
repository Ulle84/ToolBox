// created on 2017-04-18 by Ulrich Belitz

#include <QWidget>

#include "WidgetGeometry.h"
#include "Converter.h"

namespace WidgetGeometry
{
  void SHARED_API save(const QWidget* widget, QJsonObject& jsonObject)
  {
    QJsonObject geometry;
    geometry["top"] = widget->geometry().top();
    geometry["left"] = widget->geometry().left();
    geometry["width"] = widget->geometry().width();
    geometry["height"] = widget->geometry().height();
    geometry["maximized"] = widget->isMaximized();

    jsonObject["geometry"] = geometry;
  }

  void SHARED_API load(QWidget* widget, const QJsonObject& jsonObject)
  {
    if (!jsonObject.contains("geometry"))
    {
      return;
    }

    QJsonObject geometry = jsonObject["geometry"].toObject();

    if (geometry["maximized"].toBool())
    {
      widget->showMaximized();
    }
    else
    {
      int left = geometry["left"].toInt(0);
      int top = geometry["top"].toInt(0);
      int width = geometry["width"].toInt(640);
      int height = geometry["height"].toInt(480);

      widget->setGeometry(QRect(left, top, width, height));
    }
  }
}

