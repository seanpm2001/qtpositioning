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

#include "qdoublevector2d_p.h"
#include "qdoublevector3d_p.h"
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE

QDoubleVector2D::QDoubleVector2D(const QDoubleVector3D &vector) :
    xp(vector.xp), yp(vector.yp)
{
}

double QDoubleVector2D::length() const
{
    return qSqrt(xp * xp + yp * yp);
}

QDoubleVector2D QDoubleVector2D::normalized() const
{
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp);
    if (qFuzzyIsNull(len - 1.0))
        return *this;
    else if (!qFuzzyIsNull(len))
        return *this / (double)qSqrt(len);
    else
        return QDoubleVector2D();
}

void QDoubleVector2D::normalize()
{
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp);
    if (qFuzzyIsNull(len - 1.0) || qFuzzyIsNull(len))
        return;

    len = qSqrt(len);

    xp /= len;
    yp /= len;
}

QDoubleVector3D QDoubleVector2D::toVector3D() const
{
    return QDoubleVector3D(xp, yp, 0.0);
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<(QDebug dbg, const QDoubleVector2D &vector)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "QDoubleVector2D(" << vector.x() << ", " << vector.y() << ')';
    return dbg;
}

#endif

#ifndef QT_NO_DATASTREAM

QDataStream &operator<<(QDataStream &stream, const QDoubleVector2D &vector)
{
    stream << double(vector.x()) << double(vector.y());
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QDoubleVector2D &vector)
{
    double x, y;
    stream >> x;
    stream >> y;
    vector.setX(double(x));
    vector.setY(double(y));
    return stream;
}

#endif // QT_NO_DATASTREAM

QT_END_NAMESPACE
