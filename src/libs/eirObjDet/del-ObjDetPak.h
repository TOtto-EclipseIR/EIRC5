#pragma once
#include "eirObjDet.h"

#include <QFileInfo>
#include <QQueue>

#include <eirType/QQByteArray.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQImage.h>
#include <eirType/ValuePak.h>

class EIROBJDET_EXPORT ObjDetPak : public ValuePak
{
public:
    enum ImageIndex
    {
        nullImageIndex = 0,
        InputImageIndex,
        sizeImageIndex
    };

public:
    typedef QQueue<ObjDetPak> Queue;
    typedef QMap<Uuid, ObjDetPak> UuidMap;

public:
    ObjDetPak();
    ObjDetPak(const QQFileInfo &fileInfo, const bool load=true);
    ObjDetPak(const QQByteArray &bytes, const bool load=true);
    QQFileInfo inputImageFileInfo() const;
    QQByteArray inputImageBytes() const;
    QQImage inputImage() const;
    void setInputFileInfo(const QQFileInfo &fileInfo);
    void setInputBytes(const QQByteArray &bytes);
    void loadInputImage(const QQFileInfo &fileInfo);
    void loadInputImage(const QQByteArray &bytes);
    void loadInputImage();

protected:
    QQImage getImage(const ImageIndex iix) const;
    void setImage(const ImageIndex iix,
                  const QQImage &image);
};

EIROBJDET_EXPORT QDebug operator<<(QDebug dbg, const ObjDetPak &pak);
