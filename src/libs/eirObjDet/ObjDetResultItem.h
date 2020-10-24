#pragma once
#include "eirObjDet.h"

#include <QMetaType>

#include <eirType/QQRect.h>
#include <eirType/QQRectF.h>
#include <eirType/QQRectList.h>
#include <eirQtCV/cvClassifier.h>

class EIROBJDET_EXPORT ObjDetResultItem
{
public:
    ObjDetResultItem();
    ObjDetResultItem(const cvClassifier::Parameters &parms);
    void setParameters(const cvClassifier::Parameters &parms);
    bool isEmpty() const;
    void unite(const QQRect rect);
    bool unite(const QQRect rect, const qreal overlapThreshold);
    void accumulate(const QQRect rect);
    bool isOrphan(const int threshold=1) const;
    void calculate(const cvClassifier *classifier);
    QQRect united() const;
    qreal unitedOverlap(const QQRect rect) const;

    QQRect resultRect() const;
    QQRectList allRects() const;
    qreal averageOverlap() const;
    int rank() const;
    int quality(const int ifZero=0) const;
    int count() const;

    void setRank(const int rank);
    QString toString() const;
    void dump(int verbosity=0) const;

private:
    cvClassifier::Parameters mParameters;
    QQRect mResultRect;
    QQRect mUnitedRect;
    QQRectF mAccumulator;
    qreal mOverlapAccumulator=0.0;
    QQRectList mAccumulatedRects;
    int mQuality=0;
    int mRank=0;
};
Q_DECLARE_METATYPE(ObjDetResultItem);

EIROBJDET_EXPORT QDebug operator<<(QDebug dbg, const ObjDetResultItem &item);

