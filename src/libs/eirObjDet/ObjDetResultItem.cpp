#include "ObjDetResultItem.h"

#include <cmath>

#include <eirXfr/Debug.h>

ObjDetResultItem::ObjDetResultItem() {;}
ObjDetResultItem::ObjDetResultItem(const cvCascade::Parameters &parms)
    : mParameters(parms) {;}

void ObjDetResultItem::setParameters(const cvCascade::Parameters &parms)
{
    mParameters = parms;
}

bool ObjDetResultItem::isEmpty() const
{
    return mAccumulatedRects.isEmpty();
}

void ObjDetResultItem::unite(const QQRect rect)
{
    if (mAccumulatedRects.isEmpty())
    {
        mUnitedRect = rect;
    }
    else
    {
        mOverlapAccumulator += unitedOverlap(rect);
        mUnitedRect &= rect;
    }
    mAccumulatedRects.append(rect);
    TRACEQFI << mAccumulatedRects.size() << mUnitedRect
             << mOverlapAccumulator << mOverlapAccumulator / (mAccumulatedRects.size()-1);
}

bool ObjDetResultItem::isOrphan() const
{
    return 1 == mAccumulatedRects.size();
}

void ObjDetResultItem::calculate()
{
    TRACEQFI << mAccumulator << mUnitedRect;
    TODO(UnSmell);
    EXPECTNOT(isEmpty());
    EXPECTNOT(isOrphan());
    EXPECTGT(count(), 1);
    if (mAccumulator.isValid() && count() > 1)
        mResultRect = mAccumulator / count();
    else if (mUnitedRect.isValid())
        mResultRect =mUnitedRect;
    mResultRect.makeSquare();
    TRACE << mResultRect;

    qreal qualityF = log(count()) * 900.0 / 4.0;
    qualityF *= averageOverlap();
    TODO(UpScale by width from min to max width);
    TODO(Adjust for Factor);
    mQuality = qBound(1, qRound(qualityF), 999);
    TRACE << count() << log(count()) << averageOverlap() << qualityF;
}

qreal ObjDetResultItem::unitedOverlap(const QQRect rect) const
{
    return mUnitedRect.overlap(rect);
}

QQRect ObjDetResultItem::resultRect() const
{
    return mResultRect;
}

QQRectList ObjDetResultItem::allRects() const
{
    return mAccumulatedRects;
}

qreal ObjDetResultItem::averageOverlap() const
{
    return count() > 1
            ? mOverlapAccumulator / qreal(count() - 1)
            : 0.0;
}

int ObjDetResultItem::quality(const int ifZero) const
{
    return mQuality ? mQuality : ifZero;
}

int ObjDetResultItem::count() const
{
    return mAccumulatedRects.size();
}

void ObjDetResultItem::setRank(const int rank)
{
    mRank = rank;
}

QString ObjDetResultItem::toString() const
{
    return QString("%1. Q%2 %3 (%4/%5 %6)")
                .arg(mRank, 2).arg(mQuality, 3).arg(mResultRect)
                .arg(mAccumulator.toString()).arg(mAccumulatedRects.size())
                .arg(mUnitedRect);;
}

void ObjDetResultItem::dump(int verbosity) const
{
    DUMP << toString();
    if (verbosity >= 1)
        DUMP << mAccumulatedRects;
}

QDebug operator<<(QDebug dbg, const ObjDetResultItem &item)
{
    dbg << item.toString();
    return dbg;
}
