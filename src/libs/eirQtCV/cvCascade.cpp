#include "cvCascade.h"

#include <QDomElement>
#include <QColor>
#include <QTextStream>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
    : cmType(type)
{
    TRACEQFI << type;
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

bool cvCascade::isNull() const
{
    return nullType == cmType;
}

bool cvCascade::loadCascade(const QQFileInfo &cascadeXmlInfo)
{
    TRACEQFI << typeName()() << cascadeXmlInfo.absoluteFilePath();
    unload();
    EXPECT(cascadeFileInfo().exists());
    EXPECT(cascadeFileInfo().isFile());
    EXPECT(cascadeFileInfo().isReadable());
    if (cascadeFileInfo().notExists()
            || cascadeFileInfo().notFile()
            || cascadeFileInfo().notReadable())
        return false;                                               /* /========\ */
    cv::CascadeClassifier * pcvcc = new cv::CascadeClassifier;
    if (pcvcc->load(cvString(cascadeXmlInfo.absoluteFilePath())))
    {
        mpClassifier = pcvcc;
        mCascadeXmlInfo = cascadeXmlInfo;
        EXPECTNOT(mpClassifier->empty());
        EXPECTNOT(mpClassifier->empty());
    }
    return nullptr != mpClassifier;
}

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

bool cvCascade::notLoaded() const
{
    return mpClassifier ? mpClassifier->empty() : true;
}

bool cvCascade::isLoaded() const
{
    return mpClassifier ? ( ! mpClassifier->empty()) : false;
}

void cvCascade::unload()
{
    if (mpClassifier)
    {
        delete mpClassifier;
        mpClassifier = nullptr;
    }
    mCascadeXmlInfo = QFileInfo();
    mCoreSize = QSize();
}

QSize cvCascade::coreSize() const
{
    TRACEQFI << mCoreSize;
    return mCoreSize;
}

QQFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::classifier()
{
    return mpClassifier;
}

int cvCascade::detectRectangles(const SettingsFile::Map &rectFinderSettingsMap,
                                const QQImage &inputImage,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << inputImage << region;
    rectFinderSettingsMap.dump();

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

    mParameters.set(rectFinderSettingsMap);
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
            MUSTDO(handle);
            break;
    }
    return "{unknown}";
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
