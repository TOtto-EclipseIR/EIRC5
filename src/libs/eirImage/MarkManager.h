#pragma once
#include "eirImage.h"

#include <QObject>

#include <QMap>


#include "BaseImagePak.h"
class FaceImagePak;
class FrameImagePak;

class EIRIMAGE_EXPORT MarkManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkManager(QObject *parent = nullptr);
    void add(const FrameImagePak &framepak);
    void add(const FaceImagePak &facepak);

private:
    void add(const BaseImagePak &imagepak);

signals:

private:
    QMap<Id, BaseImagePak> mIdImagePakMap;

};

Q_GLOBAL_STATIC(MarkManager, gpMarkManager);
