#pragma once

#include <QObject>
#include <QWidget>
#include "BaseImageView.h"

class FrameImageView : public BaseImageView
{
    Q_OBJECT
public:
    explicit FrameImageView(BaseImageScene *parentScene);

signals:

};

