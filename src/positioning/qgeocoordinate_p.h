/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtPositioning module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QGEOCOORDINATE_P_H
#define QGEOCOORDINATE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QSharedData>
#include "qgeocoordinate.h"

QT_BEGIN_NAMESPACE

class QGeoCoordinatePrivate : public QSharedData
{
public:
    QGeoCoordinatePrivate();
    QGeoCoordinatePrivate(const QGeoCoordinatePrivate &other);
    // The destructor needs to be virtual because we have a derived class
    // QGeoMercatorCoordinatePrivate, which is used by
    // QQuickGeoCoordinateAnimation to create QGeoCoordinate.
    virtual ~QGeoCoordinatePrivate();

    double lat;
    double lng;
    double alt;

    static void atDistanceAndAzimuth(const QGeoCoordinate &coord,
                                     qreal distance, qreal azimuth,
                                     double *lon, double *lat);
    static const QGeoCoordinatePrivate *get(const QGeoCoordinate *c) {
           return c->d.constData();
    }
};

class Q_POSITIONING_EXPORT QGeoMercatorCoordinatePrivate : public QGeoCoordinatePrivate
{
public:
    QGeoMercatorCoordinatePrivate();
    QGeoMercatorCoordinatePrivate(const QGeoMercatorCoordinatePrivate &other);
    ~QGeoMercatorCoordinatePrivate();

    double m_mercatorX;
    double m_mercatorY;
};


QT_END_NAMESPACE

#endif // QGEOCOORDINATE_P_H
