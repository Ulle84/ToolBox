// created on 2017-04-17 by Ulrich Belitz

#ifndef GEOMETRYSAVER_H
#define GEOMETRYSAVER_H

class QWidget;
class QJsonObject;

class GeometrySaver
{
public:
	GeometrySaver(QJsonObject* settings, QWidget* widget);
  ~GeometrySaver();

private:
	QJsonObject* m_settings;
	QWidget* m_widget;
};

#endif