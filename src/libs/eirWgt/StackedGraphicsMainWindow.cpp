#include "StackedGraphicsMainWindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedWidget>

#include <eirType/QQRect.h>
#include <eirXfr/Debug.h>

#include "StackedGraphicsMainPage.h"

StackedGraphicsMainWindow::StackedGraphicsMainWindow(const Qt::WindowStates ws)
    : QMainWindow()
    , mpMainStackWidget(new QStackedWidget)
    , mpGraphicsScene(new QGraphicsScene)
    , mpGraphicsView(new QGraphicsView)
{
    TRACEQFI << ws << QOBJNAME(qApp->parent());
    setObjectName("StackedGraphicsMainWindow");
    mpMainStackWidget->setObjectName("StackedGraphicsMainWindow:QStackedWidget");
    mpGraphicsScene->setObjectName("StackedGraphicsMainWindow:QGraphicsScene");
    mpGraphicsView->setObjectName("StackedGraphicsMainWindow:QGraphicsView");
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
    setCentralWidget(mainStackWidget());
    QQRect rc(mainStackWidget()->size());
    scene()->setSceneRect(rc.toRectF());
    view()->setScene(scene());
    view()->setSceneRect(rc.toRectF());
    show();
}
