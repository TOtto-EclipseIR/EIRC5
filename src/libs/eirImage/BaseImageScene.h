#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

class BaseImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    BaseImageScene(QObject *parent = nullptr);
};

