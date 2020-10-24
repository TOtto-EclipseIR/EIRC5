#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifier.h>

class EIROBJDET_EXPORT RectangleGrouper : public QObject
{
    Q_OBJECT
public:
    explicit RectangleGrouper(const cvClassifier::Type cascadeType, const Settings::Key grouperKey, QObject *parent = nullptr);

public slots:
    void initialize();

signals:
    void setupFinished(const cvClassifier::Type type);

private:
    cvClassifier::Type cmType;
    Settings::Key cmGrouperKey;
};

