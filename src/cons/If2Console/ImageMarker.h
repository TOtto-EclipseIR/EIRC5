#pragma once

#include <QPoint>

#include <eirType/QQRect.h>
#include <eirExe/ConfigObject.h>

#include "MarkedFrame.h"
// #include "MarkedFace.h"


class ImageMarker
{
public:
    class Frame
    {

    };

    class Face
    {
    public:
        typedef QList<Face> List;

    public:
        Face();
    };

public:
    ImageMarker();
    void configure();
    void setFrame(const QImage & frameImage);
    void setFace(const int index,
                 const QQRect rc,
                 const QLine eyeLine);
    Configuration frameConfig() const;
    Configuration faceConfig() const;

private:
    ConfigObject * mpConfig;
    Frame mFrame;
    Face::List mFaceList;
};

