#pragma once
#include "eirType.h"

#include <QSize>

class EIRTYPE_EXPORT QQSize : public QSize
{
public:
    QQSize();
    QQSize(const QSize qsz);
    QQSize(const QQSize &other);
    QQSize(const int width, const int height);
    //QQSize(const int width, const int height, const int truncate);
    qreal aspect() const;
    int minDimension() const;
    int area() const;
    void setByWidth(int width, qreal aspect);
    void nullify();
    static QQSize null;
};

