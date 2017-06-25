/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QTime>
#include <QtCore/QDebug>

// Test: hover on data point -> show label with x and y value
// Test: zoom and move

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    qsrand((uint) QTime::currentTime().msec());

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_timer.setInterval(m_updateInterval);

    m_series = new QLineSeries(this);
    m_series->setPointsVisible(true);
    //m_series->setPointLabelsVisible(true);
    //m_series->setPointLabelsFont(QFont("Monaco", 14));
    //m_series->setPointLabelsFormat("y: @yPoint");

    //QDateTime dt1 = QDateTime::fromString("2017-06-06 20:39:00.000", "yyyy-MM-dd hh:mm:ss.zzz");
    //QDateTime dt2 = QDateTime::fromString("2017-06-06 20:39:00.001", "yyyy-MM-dd hh:mm:ss.zzz");
    //
    //qDebug() << dt2.toMSecsSinceEpoch() - dt1.toMSecsSinceEpoch();

    //m_series->append(QDateTime::fromString("2017-06-06 22:04:00.000", "yyyy-MM-dd hh:mm:ss.zzz").toMSecsSinceEpoch(), 1.0);
    //m_series->append(QDateTime::fromString("2017-06-06 22:04:00.000", "yyyy-MM-dd hh:mm:ss.zzz").toMSecsSinceEpoch(), 2.0);
    //m_series->append(QDateTime::fromString("2017-06-06 22:04:00.000", "yyyy-MM-dd hh:mm:ss.zzz").toMSecsSinceEpoch(), 3.0);
    //m_series->append(QDateTime::fromString("2017-06-06 22:04:00.002", "yyyy-MM-dd hh:mm:ss.zzz").toMSecsSinceEpoch(), 4.0);
    //m_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), 5.0);
    //m_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), 6.0);
    //m_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), 7.0);


    //m_series->append(QDateTime::fromString("2017-06-06 20:39:04", "yyyy-MM-dd hh:mm:ss").toMSecsSinceEpoch(), 1.0);
    //m_series->append(QDateTime::fromString("2017-06-06 20:39:05", "yyyy-MM-dd hh:mm:ss").toMSecsSinceEpoch(), 1.0);

    //for (int i = 0; i < 10; ++i)
    //{
    //  m_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), i);
    ////
    //}

    addSeries(m_series);




    m_xAxis = new QDateTimeAxis;
    m_xAxis->setTickCount(m_duration / 1000 + 1);
    m_xAxis->setFormat("hh:mm:ss");
    m_xAxis->setTitleText("Time");
    addAxis(m_xAxis, Qt::AlignBottom);
    m_series->attachAxis(m_xAxis);

    m_yAxis = new QValueAxis;
    m_yAxis->setLabelFormat("%i");
    m_yAxis->setTitleText("Value");
    m_yAxis->setRange(-1, 11);
    addAxis(m_yAxis, Qt::AlignLeft);
    m_series->attachAxis(m_yAxis);



    // QLineSeries
    // QSplineSeries
    QPen pen(Qt::red);
    pen.setWidth(3);
    m_series->setPen(pen);
    //m_series->append(m_x, m_y);


    //createDefaultAxes();
    //addAxis(m_axis, Qt::AlignBottom);

    //m_axis->setFormat("hh:mm:ss");
    //setAxisX(m_axis, m_series);
    //m_axis->setTickCount(3);
    //axisX()->setRange(0, 10);
    //axisY()->setRange(-1, 11);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    //qreal x = plotArea().width() / m_axis->tickCount();
    //qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
   // m_x += y;
   // m_y = qrand() % 10;
   // m_series->append(m_xValue, qrand() % 10);
   //


    //axisX()->setRange(m_xValue - (10 * m_updateInterval / 1000), m_x - 1);

   //if (m_series->count() > 10)
   // {
   //  m_series->remove(0);
   //}

  qint64 currentDateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

  m_series->append(currentDateTime, qrand() % 10);
  //m_xAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()), QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count() - 1).x()));

  m_xAxis->setRange(QDateTime::fromMSecsSinceEpoch(currentDateTime - m_duration), QDateTime::fromMSecsSinceEpoch(currentDateTime));

  //if (m_series->count() == 10)
  //{
  //addSeries(m_series);
  //qDebug() << "series added";
  //}






  //axisX()->setRange(m_series->at(0).x(), m_series->at(m_series->count() - 1).x());

    //m_xValue += m_updateInterval / 1000;

    //axisX()->setRange(m_series->at(0).x(), m_series->at(m_series->count() - 1).x());

    //axisY()->setRange(-1, m_y + 1);

    //scroll(1, 1);
    /*if (m_x == 100)
        m_timer.stop();*/
}
