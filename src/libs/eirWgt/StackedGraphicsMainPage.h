#pragma once

#include <QWidget>

#include <eirType/MultiName.h>

class StackedGraphicsMainWindow;

class StackedGraphicsMainPage : public QWidget
{
    Q_OBJECT
public:
    explicit StackedGraphicsMainPage(const MultiName &name, StackedGraphicsMainWindow *mainWin);
    StackedGraphicsMainWindow * mainWindow()    { return mpMainWindow; }


signals:


private:
    StackedGraphicsMainWindow * mpMainWindow;
};

