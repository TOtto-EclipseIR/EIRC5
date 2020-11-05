#pragma once

#include <QObject>
#include <QWidget>
#include "BaseImageView.h"

class FaceImageView : public BaseImageView
{
    Q_OBJECT
public:
    explicit FaceImageView(BaseImageScene *parentScene);

signals:

};

