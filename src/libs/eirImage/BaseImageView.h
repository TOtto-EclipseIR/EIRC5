#pragma once

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

#include "BaseImageScene.h"

class BaseImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BaseImageView(BaseImageScene *parentScene);

signals:

};

