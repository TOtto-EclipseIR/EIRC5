#include "ObjectDetector.h"

#include <QTimer>

#include <APP>
#include <eirBase/Uuid.h>
#include <eirExe/Settings.h>
#include <eirXfr/Debug.h>

#include "ObjDetResultItem.h"
#include "ObjDetResultList.h"

QHash<cvCascadeType, ObjectDetector::This> ObjectDetector::smTypeDetectorHash;

ObjectDetector::ObjectDetector(const cvCascade::Type type,
                               QObject *parent)
    : QObject(parent)
    , mpCascade(type)
    , cmpTimer(new QTimer(parent))
{
    TRACEQFI << cvCascade::typeName(type)() << QOBJNAME(parent);
    setObjectName("ObjectDetector:"+cvCascade::typeName(type));
    TSTALLOC(cmpTimer);
    cmpTimer->setObjectName("QTimer:ObjectDetector");
    if (smTypeDetectorHash.contains(type))
    {
        ObjectDetector * oldOD = smTypeDetectorHash.value(type);
        oldOD->deleteLater();
        smTypeDetectorHash.remove(type);
    }
    smTypeDetectorHash.insert(type, this);
    EMIT(ctored());
}

ObjectDetector::~ObjectDetector()
{
    cvCascadeType type = cascade()->type();
    if (smTypeDetectorHash.contains(type)
            && smTypeDetectorHash.value(type) == this)
        smTypeDetectorHash.remove(type);
}

ObjectDetector *ObjectDetector::p(const cvCascadeType type)
{
    return smTypeDetectorHash[type];
}

cvCascade *ObjectDetector::cascade()
{
    return &mpCascade;
}

bool ObjectDetector::load(const QQFileInfo cascadeFInfo)
{
    TRACEQFI << cascadeFInfo << cascadeFInfo.isReadableFile();
    bool loaded = cascade()->loadCascade(cascadeFInfo);
    EXPECT(loaded);
    return loaded;
}

bool ObjectDetector::isLoaded()
{
    return ! cascade()->isLoaded();
}

ObjDetResultList ObjectDetector::process(const Settings::Key groupKey,
                                   const QFileInfo &inputFileInfo,
                                   bool showDetect)
{
    TRACEQFI << inputFileInfo << showDetect;
    QQImage inputImage(inputFileInfo.absoluteFilePath());
    cascade()->detectRectangles(groupKey, inputImage, showDetect);
    DUMP << cascade()->parameters();
    QQRectList rectList = cascade()->rectList();
    qreal unionGroupOverlap = STG->realPerMille("UnionGroupOverlap", 500);
    qreal unionGroupOrphan = STG->unsignedInt("UnionGroupOrphan", 1);
    ObjDetResultList resultList = groupByUnion(rectList, unionGroupOverlap, unionGroupOrphan);
    return resultList;
}

ObjDetResultList ObjectDetector::groupByUnion(const QQRectList &inputRects,
                                              const qreal overlapThreshold,
                                              const int orphanThreshold)
{
    TRACEQFI << inputRects << overlapThreshold;
    EXPECTNOT(inputRects.isEmpty());
    if (inputRects.isEmpty()) return ObjDetResultList();
    ObjDetResultList resultList;
    QQRectList remainingRects = inputRects;
    DUMPVAL(remainingRects);
    while ( ! remainingRects.isEmpty())
    {
        QQRect currentRect = remainingRects.takeFirst();
        DUMPVAL(currentRect);
        ObjDetResultItem currentItem;
        currentItem.unite(currentRect);
        QQRectList nextRects;
        while ( ! remainingRects.isEmpty())
        {
            QQRect thisRect = remainingRects.takeFirst();
            DUMPVAL(thisRect);
            if ( ! currentItem.unite(thisRect, overlapThreshold))
                nextRects << thisRect;
        }

        EXPECTNOT(currentItem.isEmpty());
        if (currentItem.isOrphan(orphanThreshold))
            resultList.appendOrphan(currentItem.allRects());
        else
            resultList.append(currentItem, cascade());
        remainingRects = nextRects;
    }
    resultList.assignRanks();
    resultList.dump(2);
    return resultList;
}

QQImage ObjectDetector::inputImageForProcess() const
{
    return mProcessInputImage;
}

void ObjectDetector::start()
{
    Milliseconds pulseMsec(mpObjDetSettings->get("PulseMsec"));
    TRACEQFI << pulseMsec;
    EXPECT(pulseMsec);
    if (pulseMsec > 0)
    {
        CONNECT(cmpTimer, &QTimer::timeout,
                this, &ObjectDetector::pulse);
        cmpTimer->start(pulseMsec);
        EMIT(started());
    }
    else
    {
        ERROR << "Timer not start()ed";
    }
}

void ObjectDetector::enqueue(const QFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    MUSTDO(it);
}

void ObjectDetector::dequeue(const int count)
{
    TRACEQFI << count;
    MUSTDO(it);

}

void ObjectDetector::release(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);

}

void ObjectDetector::stop()
{
    TRACEFN;
    DISCONNECT(cmpTimer, &QTimer::timeout,
               this, &ObjectDetector::pulse);
    EMIT(stopped());
}

void ObjectDetector::initialize(Settings *settings)
{
    TRACEFN;
    NEEDDO(anyConnect);
    mpObjDetSettings = settings;
    EMIT(initialized());
    QTimer::singleShot(100, this, &ObjectDetector::configure);
}

void ObjectDetector::configure()
{
    TRACEFN;
    mpObjDetSettings->dump();
    EMIT(configured());
    QTimer::singleShot(100, this, &ObjectDetector::setDefaults);
}

void ObjectDetector::setDefaults()
{
    TRACEFN;
    mpObjDetSettings->setDefault("PulseMsec", 64);
    mpObjDetSettings->setDefault("ProcessedHoldCount", 32);
    mpObjDetSettings->setDefault("HoldMaxIntervals", 4);
    mpObjDetSettings->setDefault("ReleasedRemoveCount", 32);
    TODO(RectFinder/TBD);
    TODO(RectGrouper/TBD);
    EMIT(defaultsSet());
    QTimer::singleShot(100, this, &ObjectDetector::readyStart);
}

void ObjectDetector::readyStart()
{
    TRACEFN;
    TODO(anything);
    EMIT(ready());
    //QTimer::singleShot(100, this, &ObjectDetector::nextslot);
}

void ObjectDetector::pulse()
{
    TRACEFN;
#if 0
    static int kHold = 0;
    int nInput      = mInputQueue.size();
    int nFinder     = mFinderQueue.size();
    int nGrouper    = mGrouperQueue.size();
    int nProcessed  = mProcessedQueue.size();
    int nReleased   = mReleasedQueue.size();

    int processedLimit  = mObjDetSettings.unsignedInt("ProcessedHoldCount");
    int holdLimit       = mObjDetSettings.unsignedInt("HoldMaxIntervals", 4);
    int releasedLimit   = mObjDetSettings.unsignedInt("ReleasedRemoveCount");
    DUMP << "Pulse:"
         << nInput << nFinder << nGrouper << nProcessed << nReleased;
         << processedLimit << holdLimit << releasedLimit;
    LATERDO(PerformanceRecorder);
    NEEDDO(RefactorReturns&TrackTime);
    // should we wait for client to process more?
    if (nProcessed > processedLimit)
        if (++kHold < holdLimit)
            return;                                         /*/=======\*/
    kHold = 0;

    // should we make room in the KitMap?
    if (nReleased > releasedLimit
            || (0 == nInput + nGrouper + nFinder))
    {
        while ( ! mReleasedQueue.isEmpty())
        {
            Uuid removeUuid = mReleasedQueue.dequeue();
            removeReleased(removeUuid);
        }
        return;                                             /*/=======\*/
    }

    if (nFinder >= nGrouper && nFinder >= nInput && nFinder > 0)
    {
        findRects(mFinderQueue.dequeue());
    }
    else if (nInput >= nGrouper && nInput >= nFinder && nInput > 0)
    {
        TRACE << "loadInput()" << mInputQueue.head().trace();
        loadInput(mInputQueue.dequeue());
    }
    else if (nGrouper >= nInput && nGrouper >= nFinder && nGrouper > 0)
    {
        groupRects(mGrouperQueue.dequeue());
    }
    else
    {
        ; // nothing to do, wait for next time?
    }
#endif
}

void ObjectDetector::loadInput(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);
    TRACERTV();
}

void ObjectDetector::findRects(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);
}

void ObjectDetector::groupRects(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);
}

void ObjectDetector::removeReleased(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);
}
