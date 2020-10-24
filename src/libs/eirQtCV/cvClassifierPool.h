#pragma once
#include "eirQtCV.h"

#include <QVector>

#include "cvClassifier.h"

class EIRQTCV_EXPORT cvClassifierPool
{
public:
    cvClassifierPool();
    void initialize();
    cvClassifier &r(const cvClassifier::Type type);
    BasicName::List typeNameList() const;
    QStringList statusStrings() const;

private:
    cvClassifier mClassifierArray[cvClassifier::sizeType];
};
Q_GLOBAL_STATIC(cvClassifierPool, gspClassifierPool)

extern EIRQTCV_EXPORT cvClassifier gPreScanClassifier;
extern EIRQTCV_EXPORT cvClassifier gFaceClassifier;
