#pragma once

#include <QObject>

class BaseArgumentHandler : public QObject
{
    Q_OBJECT
public:
    explicit BaseArgumentHandler(QObject *parent = nullptr);

signals:

};

