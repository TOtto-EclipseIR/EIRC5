#pragma once
#include "eirType.h"

#include <QSize>
#include <QSizeF>

#include "QQString.h"

class EIRTYPE_EXPORT QQSize : public QSize
{
public:
    QQSize();
    QQSize(const QSize qsz);
    QQSize(const QSizeF qszf);
    QQSize(const QQSize &other);
    QQSize(const int width, const int height);
    //QQSize(const int width, const int height, const int truncate);
    void set(const int width, const int height);
    void set(const QQString &str);
    qreal aspect() const;
    int minDimension() const;
    int area() const;
    void setByWidth(int width, qreal aspect);
    void nullify();
    static QQSize null;
};

