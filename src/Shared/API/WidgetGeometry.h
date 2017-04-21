// created on 2017-04-18 by Ulrich Belitz

#ifndef WIDGETGEOMETRY_H
#define WIDGETGEOMETRY_H

#include <QJsonObject>

#include "SharedAPI.h"

class QWidget;

namespace WidgetGeometry
{
	void SHARED_API save(const QWidget* widget, QJsonObject& jsonObject);
	void SHARED_API load(QWidget* widget, const QJsonObject& jsonObject);
}

#endif
