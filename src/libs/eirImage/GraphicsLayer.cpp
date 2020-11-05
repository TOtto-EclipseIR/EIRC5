#include "GraphicsLayer.h"

#include <QGraphicsRectItem>

#include <eirType/QQRect.h>

GraphicsLayer::GraphicsLayer(const QQSize sceneSize,
                             const Ratio32 initialLevel,
                             const Ratio32 initialOpacity)
    : cmSceneSize(sceneSize)
    , mLevel(initialLevel)
    , mOpacity(initialOpacity)
{
    ctor();
}

GraphicsLayer::GraphicsLayer(BaseImageScene *parentScene,
                             const Ratio32 initialLevel,
                             const Ratio32 initialOpacity)
    : mpScene(parentScene)
    , cmSceneSize(mpScene->sceneRect().size())
    , mLevel(initialLevel)
    , mOpacity(initialOpacity)
{
    ctor();
}

void GraphicsLayer::ctor()
{
    QQRect rect(cmSceneSize, QPoint(0, 0));
    QGraphicsRectItem ri(QRectF(rect), this);
    ri.setPen(Qt::NoPen);
    ri.setBrush(Qt::NoBrush);
    setOpacity(mOpacity);
    setZValue(mLevel);
}


