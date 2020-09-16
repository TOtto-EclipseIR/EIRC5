#pragma once

#include <QObject>

class OutputManager : public QObject
{
    Q_OBJECT
public:
    explicit OutputManager(QObject *parent = nullptr);

signals:

};

