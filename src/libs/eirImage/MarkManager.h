#pragma once
#include "eirImage.h"

#include <QObject>

class EIRIMAGE_EXPORT MarkManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkManager(QObject *parent = nullptr);

signals:

};

