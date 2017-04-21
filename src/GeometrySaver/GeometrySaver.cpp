// created on 2017-04-17 by Ulrich Belitz

#include <QWidget>
#include <QJsonObject>

#include "GeometrySaver.h"

GeometrySaver::GeometrySaver(QJsonObject* settings, QWidget* widget) :
m_settings(settings),
m_widget(widget)
{
	

	

	//m_widget->restoreGeometry();
}

GeometrySaver::~GeometrySaver()
{
	//m_widget->geometry();
}
