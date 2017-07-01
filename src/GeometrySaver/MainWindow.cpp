// created on 2017-04-17 by Ulrich Belitz

#include <QJsonObject>

#include "MainWindow.h"
#include "MainWindowUi.h"
#include "Converter.h"
#include "WidgetGeometry.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);
  setWindowTitle("GeometrySaver");

  // TODO simplify: WidgetGeometry::load(this, "GeometrySaver") - loads from configuration/GeometrySaver/widgetGeometry.json
  // third optional parameter: fileName, which is "mainWindowGeometry.json" by default
  QJsonObject settings = Converter::configFileToJsonObject("GeometrySaver", "settings.json");
  WidgetGeometry::load(this, settings);
}

MainWindow::~MainWindow()
{
	// TODO simplify: WidgetGeometry::save(this, "GeometrySaver") - saves to configuration/GeometrySaver/widgetGeometry.json
  QJsonObject settings;
	WidgetGeometry::save(this, settings);
	Converter::jsonObjectToConfigFile(settings, "GeometrySaver", "settings.json");


  delete ui;
}
