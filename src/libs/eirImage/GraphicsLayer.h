#pragma once

#include <QGraphicsItemGroup>

#include <eirType/QQSize.h>
#include <eirType/Ratio32.h>

#include "BaseImageScene.h"

class GraphicsLayer : public QGraphicsItemGroup
{
public:
    explicit GraphicsLayer(const QQSize sceneSize,
                           const Ratio32 initialLevel=Ratio32(0.0),
                           const Ratio32 initialOpacity=Ratio32(1.0));
    explicit GraphicsLayer(BaseImageScene *parentScene,
                           const Ratio32 initialLevel=Ratio32(0.0),
                           const Ratio32 initialOpacity=Ratio32(1.0));


private:
    void ctor(void);

signals:


private:
    BaseImageScene * mpScene=nullptr;
    const QQSize cmSceneSize;
    Ratio32 mLevel;
    Ratio32 mOpacity;

};

