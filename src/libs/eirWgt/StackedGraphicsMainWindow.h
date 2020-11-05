#pragma once
#include "eirWgt.h"

#include <QMainWindow>

#include <QMap>

#include <eirType/MultiName.h>

class StackedGraphicsMainPage;

class EIRWGT_EXPORT StackedGraphicsMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StackedGraphicsMainWindow(const Qt::WindowStates ws=Qt::WindowMaximized);
    StackedGraphicsMainPage *addPage(const MultiName &name);

signals:
    void constructed();

private slots:
    void initialize();


private:
    QMap<MultiName, StackedGraphicsMainPage *> mNamePageMap;
};

