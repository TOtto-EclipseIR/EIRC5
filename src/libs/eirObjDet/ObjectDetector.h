#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QHash>
class QTimer;

#include <eirBase/Uuid.h>
#include <eirType/Milliseconds.h>
#include <eirExe/Settings.h>
#include <eirQtCV/cvCascade.h>

#include "ObjDetResultItem.h"
#include "ObjDetResultList.h"

class EIROBJDET_EXPORT ObjectDetector : public QObject
{
    Q_OBJECT
public:
    typedef ObjectDetector * This;
public:
    ObjectDetector(const cvCascade::Type type,
                            QObject *parent = nullptr);
    ~ObjectDetector();
    static ObjectDetector * p(const cvCascadeType type);
    cvCascade * cascade();

    // single-threaded execution
    bool load(const QQFileInfo cascadeFInfo);
    bool isLoaded();
    ObjDetResultList process(Settings *settings,
                       const QFileInfo &inputFileInfo,
                       bool showDetect=false);
    QQImage inputImageForProcess() const;

private:
    ObjDetResultList groupByUnion(const QQRectList &inputRects,
                            const qreal overlapThreshold,
                            const int orphanThreshold);
    qreal calculateQuality(const ObjDetResultItem &item) const;

public slots:
    // setup
    void initialize(Settings *settings);
    void start();

    // running
    void enqueue(const QFileInfo &inputFileInfo);
    void dequeue(const int count=1);
    void release(const Uuid uuid);
    void stop();

signals:
    // setup
    void ctored();
    void initialized();
    void defaultsSet();
    void configured();
    void ready();
    void started();
    void stopped();

    // running
    void pakInserted(int count);
    void inputQueued(Uuid uuid);
    void inputQueued(int count);
    void inputQueueNotEmpty();
    void dequeueEmpty();
    void dequeueNotEmpty();
    void dequeued(Uuid uuid);
    void dequeued(int count);

    // internal TBD


private slots:
    // setup
    void configure();
    void setDefaults();
    void readyStart();

    // running
    void pulse();
    void loadInput(const Uuid uuid);
    void findRects(const Uuid uuid);
    void groupRects(const Uuid uuid);
    void removeReleased(const Uuid uuid);

private:
    cvCascade mCascade;
    QTimer  * const cmpTimer=nullptr;
    Settings *mpObjDetSettings;
    QQImage mProcessInputImage;
    Uuid::Queue mInputQueue;
    Uuid::Queue mFinderQueue;
    Uuid::Queue mGrouperQueue;
    Uuid::Queue mProcessedQueue;
    Uuid::Queue mReleasedQueue;
    static QHash<cvCascadeType, This> smTypeDetectorHash;
};

