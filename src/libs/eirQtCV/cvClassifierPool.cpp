#include "cvClassifierPool.h"

cvClassifier gPreScanClassifier(cvClassifier::PreScan);
cvClassifier gFaceClassifier(cvClassifier::Face);

cvClassifierPool::cvClassifierPool()
{
    mClassifierVector[cvClassifier::PreScan] = gPreScanClassifier;
    mClassifierVector[cvClassifier::Face] = gFaceClassifier;
}

cvClassifier &cvClassifierPool::r(const cvClassifier::Type type)
{
    return mClassifierVector[type];
}
