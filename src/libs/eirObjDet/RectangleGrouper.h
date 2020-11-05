#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifier.h>

#include "ObjDetEnum.h"
#include "ObjDetResultList.h"

class EIROBJDET_EXPORT RectangleGrouper : public QObject
{
    Q_OBJECT
public:
    struct Config
    {
        int maxResults=99;
        bool force=false;
        int minQuality=500;
        ObjDetEnum groupBy=ObjDetEnum::GroupUnion;
        qreal overlapRatio=0.500;
    };

public:
    explicit RectangleGrouper(const cvClassifier::Type cascadeType,
                              const Settings::Key grouperKey,
                              QObject *parent = nullptr);
    ObjDetEnum groupBy(const ObjDetEnum defaultBy=ObjDetEnum::GroupUnion);

public slots:
    void initialize();
    void group();

private slots:
    void configure();
    void finishSetup();
    void preScanGroup();

signals:
    void initialized(const cvClassifier::Type type);
    void configured(const cvClassifier::Type type);
    void setupFinished(const cvClassifier::Type type);
    void grouping(const cvClassifier::Type type);
    void preScanGrouped(const cvClassifier::Type type, const ObjDetResultList &odrl);

private:
    cvClassifier::Type cmType;
    Settings::Key cmGrouperKey;
    Settings::Key mGroupByKey;
};

