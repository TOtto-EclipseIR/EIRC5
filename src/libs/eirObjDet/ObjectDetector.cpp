#include "ObjectDetector.h"

#include <QTimer>

#include <eirBase/Uuid.h>
#include <eirXfr/Debug.h>

#include "ObjDetResultItem.h"
#include "ObjDetResultList.h"

QHash<cvCascadeType, ObjectDetector::This> ObjectDetector::smTypeDetectorHash;

ObjectDetector::ObjectDetector(const cvCascade::Type type,
                               ConfigObject *cfgObj,
                               QObject *parent)
    : QObject(parent)
    , mCascade(type)
    , cmpConfig(cfgObj)
    , cmpTimer(new QTimer(parent))
{
    TRACEQFI << cvCascade::typeName(type)() << QOBJNAME(parent);
    setObjectName("ObjectDetector");
    TSTALLOC(cmpConfig);
    TSTALLOC(cmpTimer);
    cmpConfig->setObjectName("ConfigObject:ObjectDetector");
    cmpTimer->setObjectName("QTimer:ObjectDetector");
    if (smTypeDetectorHash.contains(type))
    {
        ObjectDetector * oldOD = smTypeDetectorHash.value(type);
        oldOD->deleteLater();
        smTypeDetectorHash.remove(type);
    }
    smTypeDetectorHash.insert(type, this);
    EMIT(ctored());
    //QTimer::singleShot(100, this, &ObjectDetector::initialize);
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
    return &mCascade;
}

ObjDetPak &ObjectDetector::pak(const Uuid uuid)
{
    return mPakMap[uuid];
}

void ObjectDetector::insert(const ObjDetPak &pak)
{
    TRACEQFI << pak;
    mPakMap.insert(pak.uuid(), pak);
}

Uuid ObjectDetector::process(const Configuration &config,
                                   const QFileInfo &inputFileInfo,
                                   bool showDetect)
{
    TRACEQFI << inputFileInfo << showDetect;
    config.dump();
    ObjDetPak pak(inputFileInfo);
    QQImage inputImage = pak.inputImage();
    pak.set("InputImage/Configuration", config.toVariant());
    mProcessInputImage = inputImage;
    cascade()->detectRectangles(config, inputImage, showDetect);
    pak.set(cascade()->typeName()+"/Cascade", cascade()->cascadeFileInfo());
    pak.set(cascade()->typeName()+"/CoreSize", cascade()->coreSize());
    DUMP << cascade()->parameters();
    pak.set(cascade()->typeName()+"/Parameters", cascade()->parameters().toVariant());
    pak.set(cascade()->typeName()+"/MethodString", cascade()->methodString());
    QQRectList rectList = cascade()->rectList();
    pak.set(cascade()->typeName()+"/Rectangles", rectList);
    qreal groupUnionThreshold = config.real("GroupUnionThreshold", 0.5);
    ObjDetResultList resultList = groupByUnion(rectList, groupUnionThreshold);
    pak.set(cascade()->typeName()+"/ResultList", resultList.toVariant());
    insert(pak);
    TRACE << "return uuid" << pak.uuid();
    return pak.uuid();
}

ObjDetResultList ObjectDetector::groupByUnion(const QQRectList &inputRects,
                                        const qreal threshold)
{
    TRACEQFI << inputRects << threshold;
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
        {
            while ( ! remainingRects.isEmpty())
            {
                QQRect thisRect = remainingRects.takeFirst();
                DUMPVAL(thisRect);
                if (currentItem.unitedOverlap(thisRect) > threshold)
                    currentItem.unite(thisRect);
                else
                    nextRects << thisRect;
            }
        }
        if (currentItem.isOrphan())
        {
            resultList.appendOrphan(currentRect);
        }
        else if (currentItem.isEmpty())
        {
            EXPECTNOT(currentItem.isEmpty());
        }
        else
        {
            currentItem.calculate();
            resultList.append(currentItem);
        }
        remainingRects = nextRects;
    }
    resultList.assignRanks();
    resultList.dump(2);
    return resultList;
}

QQImage ObjectDetector::processInputImage() const
{
    return mProcessInputImage;
}

void ObjectDetector::start()
{
    Milliseconds pulseMsec = mObjDetConfig.signedInt("PulseMsec");
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
    bool autoLoad = mObjDetConfig.boolean("InputQueue/AutoLoad");
    TRACEQFI << inputFileInfo << autoLoad;
    ObjDetPak pak(inputFileInfo, autoLoad);
    Uuid uuid = pak.uuid();
    DUMPVAL(uuid);
    mPakMap.insert(uuid, pak);
    EMIT(pakInserted(mPakMap.size()));
    if ( ! autoLoad)
    {
        mInputQueue.enqueue(uuid);
        EMIT(inputQueued(uuid));
        EMIT(inputQueued(mInputQueue.size()));
        EMIT(inputQueueNotEmpty());
    }
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

void ObjectDetector::initialize()
{
    TRACEFN;
    NEEDDO(anyConnect);
    EMIT(initialized());
    QTimer::singleShot(100, this, &ObjectDetector::setDefaults);
}

void ObjectDetector::setDefaults()
{
    TRACEFN;
    mObjDetConfig.setDefault("PulseMsec", 64);
    mObjDetConfig.setDefault("ProcessedHoldCount", 32);
    mObjDetConfig.setDefault("HoldMaxIntervals", 4);
    mObjDetConfig.setDefault("ReleasedRemoveCount", 32);
    mObjDetConfig.setDefault("InputQueue/AutoLoad", false);
    TODO(RectFinder/TBD);
    TODO(RectGrouper/TBD);
    EMIT(defaultsSet());
    QTimer::singleShot(100, this, &ObjectDetector::configure);
}

void ObjectDetector::configure()
{
    TRACEFN;
    mObjDetConfig += cmpConfig->configuration().
            extract(cascade()->typeName()+"/ObjectDetector");
    LATERDO("connectDispatcher");
    EMIT(configured());
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
    static int kHold = 0;
    int nPak        = mPakMap.size();
    int nInput      = mInputQueue.size();
    int nFinder     = mFinderQueue.size();
    int nGrouper    = mGrouperQueue.size();
    int nProcessed  = mProcessedQueue.size();
    int nReleased   = mReleasedQueue.size();

    int processedLimit  = mObjDetConfig.unsignedInt("ProcessedHoldCount");
    int holdLimit       = mObjDetConfig.unsignedInt("HoldMaxIntervals", 4);
    int releasedLimit   = mObjDetConfig.unsignedInt("ReleasedRemoveCount");
    DUMP << "Pulse:" << nPak
         << nInput << nFinder << nGrouper << nProcessed << nReleased
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
}

void ObjectDetector::loadInput(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    pak(uuid).loadInputImage();
    if ( ! pak(uuid).inputImage().isNull())
        mFinderQueue.enqueue(uuid);
    else
        ERROR << "inputImage() null" << uuid.trace();
    TRACERTV();
}

void ObjectDetector::findRects(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    QQImage inputImage = pak(uuid).inputImage();
    if (inputImage.isNull())
    {
        ERROR << "inputImage() null" << uuid.trace();
    }
    else
    {
        int rects = cascade()->detectRectangles(Configuration(), inputImage);
        if (rects < 0)
            ERROR << "detectRectangles() Error:" << rects;
        else if (0 == rects)
            WARN << "No Rectangles Detected";
        else
            TRACE << rects << "Detectected";
    }
    MUSTDO(saveRectsAndEnqueueGrouper);
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
