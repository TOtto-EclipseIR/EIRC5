#include "StackedGraphicsMainWindow.h"

#include <QApplication>

#include <eirXfr/Debug.h>

#include "StackedGraphicsMainPage.h"

StackedGraphicsMainWindow::StackedGraphicsMainWindow(const Qt::WindowStates ws)
    : QMainWindow()
{
    TRACEQFI << ws << QOBJNAME(qApp->parent());
    setObjectName("StackedGraphicsMainWindow");
    setWindowState(ws);
    CONNECT(this, &StackedGraphicsMainWindow::constructed,
            this, &StackedGraphicsMainWindow::initialize);
    EMIT(constructed());
}

StackedGraphicsMainPage *StackedGraphicsMainWindow::addPage(const MultiName &name)
{
    TRACEQFI << name();
    StackedGraphicsMainPage * page = new StackedGraphicsMainPage(name, this);
    MUSTDO(more);
    return page;
}

void StackedGraphicsMainWindow::initialize()
{
    TRACEQFI << QOBJNAME(this);
    show();
}
