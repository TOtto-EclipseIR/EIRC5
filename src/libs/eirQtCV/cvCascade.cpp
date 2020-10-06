#include "cvCascade.h"

#include <QDomElement>
#include <QColor>
#include <QTextStream>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/types.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvRect.h"
#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
    : cmType(type)
    , mpClassifier(new cv::CascadeClassifier())
{
    TRACEQFI << type;
    TSTALLOC(mpClassifier);
    TODO(cv::redirectError);
}

cvCascade::Type cvCascade::type() const
{
    return cmType;
}

BasicName cvCascade::typeName() const
{
    return typeName(cmType);
}

bool cvCascade::loadCascade(const QQFileInfo &cascadeXmlInfo)
{
    TRACEQFI << typeName()() << cascadeXmlInfo.absoluteFilePath();
    EXPECT(mpClassifier->load(cvString(cascadeXmlInfo.absoluteFilePath())));
    mCascadeXmlInfo = cascadeXmlInfo;
    return isLoaded();
}

bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mpClassifier->empty();
}

QSize cvCascade::coreSize() const
{
    TSTALLOC(mpClassifier);
    cv::Size cvsz = mpClassifier->getOriginalWindowSize();
    QSize qsz(cvsz.width, cvsz.height);
    TRACEQFI << qsz;
    return qsz;
}

QQFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::classifier()
{
    return mpClassifier;
}

#if 0
int cvCascade::detectRectangles(const Settings::Key &groupKey,
                                const QQImage &inputImage,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << inputImage << region;
    TSTALLOC(mpClassifier);

    EXPECTNOT(inputImage.isNull());
    if (inputImage.isNull()) return -1; // null image       /* /========\ */
    mMethodString.clear();
    mDetectMat.clear();
    mRectList.clear();

    mDetectMat = cvMat::greyFromImage(inputImage);
    DUMP << mDetectMat.toDebugString();
    if (mDetectMat.isNull()) return -2; // null cvMat       /* /========\ */
    if (showDetect)
    {
        cv::imshow("DetectMat", mDetectMat.mat());
        cv::waitKey(5000);
    }

    if (notLoaded()) return -3;         // empty cascade    /* /========\ */
    mParameters.set(groupKey);
    mParameters.calculate(cmType, mDetectMat.size(), coreSize());
#if 0
    cvSize minSize = mParameters.minSize();
    cvSize maxSize = mParameters.maxSize();
#else
    NEEDDO(RemoveForFlight);
    cvSize minSize(0,0);
    cvSize maxSize(0,0);
#endif
    mMethodString = mParameters.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;

    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
                        minSize, maxSize);

    foreach (cvRect cvrc, cvRectVector) mRectList << cvrc.toRect();
    return mRectList.size();
}
#endif

int cvCascade::detectRectangles(const QSettings::SettingsMap rectSettings,
                                #ifdef QTCV_SETTINGS_HACK
                                    const unsigned scaleFactor,
                                    const signed neighbors,
                                    const unsigned minQuality,
                                #endif

                                const cvMat &greyInputMat,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << showDetect << region;
    Settings::dump(rectSettings);
    DUMP << mDetectMat.toDebugString();
    TSTALLOC(mpClassifier);

    mMethodString.clear();
    mDetectMat.clear();
    mRectList.clear();

    EXPECTNOT(greyInputMat.isNull());
    mDetectMat = greyInputMat;
    if (mDetectMat.isNull()) return -2; // null cvMat       /* /========\ */
    if (showDetect)
    {
        cv::imshow("DetectMat", mDetectMat.mat());
        cv::waitKey(5000);
    }

    EXPECT(isLoaded());
    if (notLoaded()) return -3;         // empty cascade    /* /========\ */
#ifdef QTCV_SETTINGS_HACK
    mParameters.calculate(scaleFactor, neighbors, minQuality);
#else
    mParameters.calculate(rectSettings, cmType, mDetectMat.size(), coreSize());
#endif
#if 0
    cvSize minSize = mParameters.minSize();
    cvSize maxSize = mParameters.maxSize();
#else
    NEEDDO(RemoveForFlight);
    cvSize minSize(0,0);
    cvSize maxSize(0,0);
#endif
    mMethodString = mParameters.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;
    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
                        minSize, maxSize);

    foreach (cvRect cvrc, cvRectVector) mRectList << cvrc.toRect();
    return mRectList.size();
}
#if 0
int cvCascade::detectRectangles(Settings *rectFinderSettings,
                                const QQImage &inputImage,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << inputImage << region;
    rectFinderSettings->dump();

    EXPECTNOT(inputImage.isNull());
    if (inputImage.isNull()) return -1; // null image       /* /========\ */
    mMethodString.clear();
    mDetectMat.clear();
    mRectList.clear();

    mDetectMat.setGrey(inputImage);
    DUMP << mDetectMat.dumpString();
    if (mDetectMat.isNull()) return -2; // null cvMat       /* /========\ */
    if (showDetect)
    {
        cv::imshow("DetectMat", mDetectMat.mat());
        cv::waitKey(5000);
    }

    EXPECTNE(nullptr, mpClassifier);
    if (nullptr == mpClassifier)
        return -3;                                          /* /========\ */

    mParameters.set(rectFinderSettings);
    mParameters.calculate(cmType, mDetectMat.size(), coreSize());
#if 0
    QSize minSize = mParameters.minSize();
    QSize maxSize = mParameters.maxSize();
#else
    NEEDDO(RemoveForFlight);
    QSize minSize(0,0);
    QSize maxSize(0,0);
#endif
    mMethodString = mParameters.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;
    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));

    foreach (cv::Rect cvrc, cvRectVector)
        mRectList << QQRect(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
    return mRectList.size();
}
#endif
cvMat cvCascade::detectMat() const
{
    return mDetectMat;
}

QQImage cvCascade::detectImage() const
{
    return mDetectMat.toGreyImage();
}

QQRectList cvCascade::rectList() const
{
    return mRectList;
}

QString cvCascade::methodString() const
{
    return mMethodString;
}

cvCascade::Parameters cvCascade::parameters() const
{
    return mParameters;
}

BasicName cvCascade::typeName(cvCascade::Type type)
{
    switch (type)
    {
        case nullType:      return "{null}";
        case PreScan:       return "PreScan";
        default:
            MUSTDO(type);
            break;
    }
    return "{unknown}";
}

#if 0
bool cvCascade::loadCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cmType << cascadeXmlInfo;
    mCoreSize = QSize();

    XmlFile xmlFile(cascadeXmlInfo.absoluteFilePath());
    bool loaded = xmlFile.load();
    EXPECT(loaded);
    if ( ! loaded) return loaded;

    QDomElement rootDE = xmlFile.rootElement();
    DUMPVAL(rootDE.tagName());
    QDomElement topDE = rootDE.firstChildElement();
    DUMPVAL(topDE.tagName());
    DUMPVAL(topDE.attribute("type_id"));

    int cascadeVersion = determineVersion(topDE);
    QSize sz;
    switch (cascadeVersion)
    {
    case 2:     sz = getSize2(topDE);       break;
    case 4:     sz = getSize2(topDE);       break;
    default:    return false;
    }

    DUMPVAL(sz);
    if (sz.isValid()) mCoreSize = sz;
    return mCoreSize.isValid();
}

int cvCascade::determineVersion(const QDomElement topDE)
{
    TRACEQFI << topDE.text();
    int ver = -1;
    QString typeId = topDE.attribute("type_id");
    if (typeId == "opencv-haar-classifier")
        ver = 2;
    else if (typeId == "opencv-cascade-classifier")
        ver = 4;
    EXPECTNE(-1, ver);
    return ver;
}

QQSize cvCascade::getSize2(const QDomElement topDE)
{
    TRACEQFI << topDE.text();
    int width = -1, height = -1;
    QDomElement sizeDE = topDE.firstChildElement("size");
    QString sizeText = sizeDE.text();
    QTextStream ts(&sizeText);
    ts >> width >> height;
    return QQSize(width, height);
}

QQSize cvCascade::getSize4(const QDomElement topDE)
{
    TRACEQFI << topDE.text();
    int width = -1, height = -1;
    QDomElement heightDE = topDE.firstChildElement("height");
    QDomElement widthDE  = topDE.firstChildElement("width");
    height = heightDE.text().toInt();
    width  = widthDE.text().toInt();
    return QQSize(width, height);
}
#endif
