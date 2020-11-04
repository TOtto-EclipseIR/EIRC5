#include "RectangleGrouper.h"

#include <APP>
#include <eirXfr/Debug.h>

#include "ObjDetEnum.h"
#include "ObjDetProcessor.h"
#include "ObjectDetection.h"
#include "ObjDetResultItem.h"
#include "ObjDetResultList.h"

RectangleGrouper::RectangleGrouper(const cvClassifier::Type cascadeType,
                                   const Settings::Key grouperKey,
                                   QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmGrouperKey(grouperKey)
{
    TRACEQFI << cvClassifier::typeName(cascadeType)() << grouperKey() << QOBJNAME(parent);
    setObjectName("RectangleGrouper:"+cvClassifier::typeName(cascadeType));
}

ObjDetEnum RectangleGrouper::groupBy(const ObjDetEnum defaultBy)
{
    TRACEQFI << defaultBy;
    STG->beginGroup(cmGrouperKey);
    QString groupByString = STG->string("GroupBy", defaultBy.name());
    ObjDetEnum enumGroup(groupByString);
    STG->endGroup();
    return (ObjDetEnum::GroupByBefore < enumGroup
                && enumGroup < ObjDetEnum::GroupByAfter)
                    ? enumGroup : defaultBy;
}

void RectangleGrouper::initialize()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    CONNECT(this, &RectangleGrouper::initialized,
            this, &RectangleGrouper::group);
    CONNECT(this, &RectangleGrouper::initialized,
            this, &RectangleGrouper::group);
    if (cvClassifier::PreScan == cmType)
    {
        CONNECT(this, &RectangleGrouper::grouping,
                this, &RectangleGrouper::preScanGroup);
    }
    else
    {
        MUSTDO(it);
    }
    EMIT(initialized(cmType));
}

void RectangleGrouper::group()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    EMIT(grouping(cmType));
}

void RectangleGrouper::configure()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    STG->beginGroup(cmGrouperKey);

    STG->endGroup();
    MUSTDO(More);
}

void RectangleGrouper::finishSetup()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    MUSTDO(it);
    EMIT(setupFinished(cmType));
}

void RectangleGrouper::preScanGroup()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    MUSTDO(it);
    ObjDetProcessor * proc = OBJD->processor(cmType);
    QQRectList inputRects = proc->rectangleList();
    ObjDetEnum groupMethod = groupBy();
    ObjDetResultList results;

    while (inputRects.notEmpty())
    {
        ObjDetResultItem thisResult;
    }

}

