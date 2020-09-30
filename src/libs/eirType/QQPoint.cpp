#include "QQPoint.h"

QQPoint::QQPoint() {;}
QQPoint::QQPoint(const int x, const int y) : QPoint(x, y) {;}
QQPoint::QQPoint(const int index, const QQSize size)
    : QPoint(index % size.width(), index / size.width()) {;}
