#pragma once
#include "eirObjDet.h"

#include <QList>
#include <QMetaType>
#include <QMultiMap>

#include <eirType/QQRectList.h>

#include "ObjDetResultItem.h"

class EIROBJDET_EXPORT ObjDetResultList
{
public:
    ObjDetResultList();
    ~ObjDetResultList();
    void clear();
    void set(const QVariant &variant);
    QList<ObjDetResultItem> list() const;
    ObjDetResultItem at(const int rank) const;
    void appendOrphan(const QQRectList rect);
    void append(ObjDetResultItem item, const cvClassifier *classifier);
    void assignRanks();
    int count() const;
    int orphanCount() const;
    QQRectList orphanRects() const;
    QVariant toVariant() const;
    void dump(int verbosity=0) const;

private:
    QMultiMap<int, ObjDetResultItem> mQualityItemMap;
    QList<ObjDetResultItem> mRankedList;
    QQRectList mOrphanRects;
    int mMaxCount=0;
};
Q_DECLARE_METATYPE(ObjDetResultList);

