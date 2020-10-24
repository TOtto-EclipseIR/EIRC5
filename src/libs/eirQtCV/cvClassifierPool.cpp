#include "cvClassifierPool.h"

#include <eirType/QQFileInfo.h>
#include <eirXfr/Debug.h>

cvClassifier gPreScanClassifier(cvClassifier::PreScan);
cvClassifier gFaceClassifier(cvClassifier::Face);

cvClassifierPool::cvClassifierPool() { TRACEFN;}

void cvClassifierPool::initialize()
{
    TRACEFN;
    gPreScanClassifier.initialize();
    gFaceClassifier.initialize();
    mClassifierArray[cvClassifier::PreScan] = gPreScanClassifier;
    mClassifierArray[cvClassifier::Face] = gFaceClassifier;
    MUSTDO(what);
}

cvClassifier &cvClassifierPool::r(const cvClassifier::Type type)
{
    Q_ASSERT(type < cvClassifier::sizeType);
    return mClassifierArray[type];
}

BasicName::List cvClassifierPool::typeNameList() const
{
    BasicName::List names;
    for (int ix = 1; ix < cvClassifier::sizeType; ++ix)
        if (mClassifierArray[ix].type() != cvClassifier::nullType)
            names << mClassifierArray[ix].typeName();
    return names;
}

QStringList cvClassifierPool::statusStrings() const
{
    QStringList qsl;
    for (int ix = 1 + cvClassifier::nullType; ix < cvClassifier::sizeType; ++ix)
    {
        cvClassifier::Type ixtype = cvClassifier::Type(ix);
        cvClassifier::Type type = mClassifierArray[ix].type();
        QQFileInfo qqfi;
        bool loaded = false;
        QQSize coreSize;
        if (cvClassifier::nullType != type)
        {
            qqfi = mClassifierArray[ix].cascadeFileInfo();
            loaded = mClassifierArray[ix].isLoaded();
            if (loaded)
                coreSize = mClassifierArray[ix].coreSize();
        }
        QString status = QString("%1: %2 %3 %4x%5 %6")
                .arg(cvClassifier::typeName(ixtype)(), 12)
                .arg(cvClassifier::typeName(type)(), -12)
                .arg(loaded ? "loaded" : "NOLOAD", 8)
                .arg(coreSize.width(), 3)
                .arg(coreSize.height(), -3)
                .arg(qqfi.completeBaseName(QQString::Squeeze));
        qsl << status;
    }
    return qsl;
}
