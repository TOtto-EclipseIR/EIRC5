#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QHash>
class QTimer;

#include <eirBase/Uuid.h>
#include <eirType/Milliseconds.h>
#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>

#include "ObjDetPak.h"
#include "ObjDetResultItem.h"
#include "ObjDetResultList.h"

class EIROBJDET_EXPORT ObjectDetector : public QObject
{
    Q_OBJECT
public:
    typedef ObjectDetector * This;
public:
    explicit ObjectDetector(const cvCascade::Type type,
                            ConfigObject * cfgObj,
                            QObject *parent = nullptr);
    ~ObjectDetector();
    static ObjectDetector * p(const cvCascadeType type);
    cvCascade * cascade();
    ObjDetPak &pak(const Uuid uuid); // non-const ref
    void insert(const ObjDetPak &pak);
    Uuid process(const Configuration &config,
                       const QFileInfo &inputFileInfo,
                       bool showDetect=false);
    ObjDetResultList groupByUnion(const QQRectList &inputRects,
                            const qreal threshold);
    qreal calculateQuality(const ObjDetResultItem &item) const;
    QQImage processInputImage() const;

public slots:
    // setup
    void initialize();
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
    void setDefaults();
    void configure();
    void readyStart();

    // running
    void pulse();
    void loadInput(const Uuid uuid);
    void findRects(const Uuid uuid);
    void groupRects(const Uuid uuid);
    void removeReleased(const Uuid uuid);

private:
    cvCascade mCascade;
    ConfigObject  * const cmpConfig=nullptr;
    QTimer  * const cmpTimer=nullptr;
    Configuration mObjDetConfig;
    QQImage mProcessInputImage;
    ObjDetPak::UuidMap mPakMap;
    Uuid::Queue mInputQueue;
    Uuid::Queue mFinderQueue;
    Uuid::Queue mGrouperQueue;
    Uuid::Queue mProcessedQueue;
    Uuid::Queue mReleasedQueue;
    static QHash<cvCascadeType, This> smTypeDetectorHash;
};

