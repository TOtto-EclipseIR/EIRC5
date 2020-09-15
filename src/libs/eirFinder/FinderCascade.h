#pragma once

#include <QImage>

#include <eirExe/ConfigObject.h>

#include <eirCascade/CascadeParameters.h>
#include <eirCascade/CascadeType.h>

class cvCascade;
class cvMat;

class FinderCascade
{
public:
    FinderCascade(const CascadeType &cascadeType,
                  ConfigObject *configObject);
    const ConfigObject *config() const;
    cvCascade *cascade();
    void clear();
    void setImage(const QImage &inputImage);
    int findRectangles();
    QList<QRect> rectList() const;
    QImage findRectImage() const;

private:
    Configuration cascadeConfig() const;
    CascadeParameters cascadeParameters() const;

private:
    const CascadeType cmCascadeType;
    const ConfigObject *cmpConfigObject=nullptr;
    cvCascade *mpCascade;
    QImage mInputImage;
    QImage mFindRectImage;
    cvMat *mpFindRectMat;
    QList<QRect> mRectList;
};

