#include "ObjDetResultList.h"

#include <eirXfr/Debug.h>


ObjDetResultList::ObjDetResultList() {;}
ObjDetResultList::~ObjDetResultList() {;}

void ObjDetResultList::clear()
{
    TRACEFN;
    mQualityItemMap.clear();
    mRankedList.clear();
    mOrphanRects.clear();
    mMaxCount = 0;
}

void ObjDetResultList::set(const QVariant &variant)
{
    *this = variant.value<ObjDetResultList>();
}

QList<ObjDetResultItem> ObjDetResultList::list() const
{
    return mRankedList;
}

void ObjDetResultList::appendOrphan(const QQRectList rect)
{
    mOrphanRects.append(rect);
}

void ObjDetResultList::append(ObjDetResultItem item, const cvClassifier *classifier)
{
    EXPECTNOT(item.isEmpty());
    EXPECTNOT(item.isOrphan());
    item.calculate(classifier);
    if ( ! item.isEmpty() && ! item.isOrphan())
        mQualityItemMap.insert( - item.quality(), item);
}

void ObjDetResultList::assignRanks()
{
    mMaxCount = 0;
    mRankedList.clear();
    foreach (ObjDetResultItem item, mQualityItemMap.values())
    {
        item.setRank(mRankedList.size()+1);
        mRankedList.append(item);
        if (item.count() > mMaxCount)
            mMaxCount = item.count();
    }
}

int ObjDetResultList::count() const
{
    return mRankedList.size();
}

int ObjDetResultList::orphanCount() const
{
    return mOrphanRects.size();
}

QQRectList ObjDetResultList::orphanRects() const
{
    return mOrphanRects;
}

QVariant ObjDetResultList::toVariant() const
{
    return QVariant::fromValue(*this);
}

void ObjDetResultList::dump(int verbosity) const
{
    DUMP << mRankedList.size() << "items";
    foreach (ObjDetResultItem item, mRankedList)
        item.dump(verbosity);
    DUMP << mOrphanRects.size() << "orphan rectangles";
    if (verbosity >= 2)
        DUMP << mOrphanRects;
    DUMPVAL(mMaxCount);
}
