#pragma once

#include <QObject>
#include <QWidget>
#include "BaseImageScene.h"

class FrameImageScene : public BaseImageScene
{
    Q_OBJECT
public:
    explicit FrameImageScene(QWidget *parent = nullptr);

signals:

};

