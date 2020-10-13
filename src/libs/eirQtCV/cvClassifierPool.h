#pragma once
#include "eirQtCV.h"

#include <QVector>

#include "cvClassifier.h"

class EIRQTCV_EXPORT cvClassifierPool
{
public:
    cvClassifierPool();
    cvClassifier &r(const cvClassifier::Type type);

private:
    QVector<cvClassifier> mClassifierVector;
};
Q_GLOBAL_STATIC(cvClassifierPool, classifierPool)

extern EIRQTCV_EXPORT cvClassifier gPreScanClassifier;
extern EIRQTCV_EXPORT cvClassifier gFaceClassifier;
