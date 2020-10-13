#include "cvSize.h"


cvSize::cvSize() : cv::Size() {;}
cvSize::cvSize(const QSize qsz) : cv::Size(qsz.width(), qsz.height()) {;}
cvSize::cvSize(const cv::Size other) : cv::Size(other) {;}
cvSize::cvSize(const int w, const int h) : cv::Size(w, h) {;}

void cvSize::nullify()
{
    set(0, 0);
}

void cvSize::set(const int w, const int h)
{
    width = w, height = h;
}

QQSize cvSize::toSize() const
{
    return QQSize(width, height);
}

bool cvSize::isValid() const
{
    return width >= 0 && height >= 0;
}

QString cvSize::toDebugString() const
{
    return QString("cvSize(%1w x %2h").arg(width).arg(height);
}

QDebug operator<<(QDebug dbg, const cvSize &cvsz)
{
    dbg << cvsz.toDebugString();
    return dbg;
}
