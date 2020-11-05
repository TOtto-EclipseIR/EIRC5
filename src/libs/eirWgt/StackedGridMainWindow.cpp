#include "StackedGridMainWindow.h"


//#include <eirXfr/Debug.h>
#include "../../../../EIRC5/src/libs/eirXfr/Debug.h"

StackedGridMainWindow::StackedGridMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mpStack(new QStackedLayout)
{
    TRACEQFI << QOBJNAME(parent);
    QWidget *centralWgt = new QWidget;
    setObjectName("StackedGridMainWindow");
    mpStack->setObjectName("StackedGridMainWindow:StackedLayout");
    centralWgt->setObjectName("StackedGridMainWindow:CentralWidget");
    centralWgt->setLayout(mpStack);
    setCentralWidget(centralWgt);
}

QWidget *StackedGridMainWindow::page(const int ix)
{
    while (stack()->count() < ix)
    {
        QWidget *stackWidget = new QWidget;
        QGridLayout *stackLayout = new QGridLayout;
        stackWidget->setLayout(stackLayout);
        stack()->addWidget(stackWidget);
    }
    return stack()->widget(ix);
}

QGridLayout *StackedGridMainWindow::layout(const int ix)
{
    return qobject_cast<QGridLayout*>(page(ix)->layout());
}

