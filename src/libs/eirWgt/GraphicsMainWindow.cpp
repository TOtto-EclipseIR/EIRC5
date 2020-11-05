#include "GraphicsMainWindow.h"

#include <eirXfr/Debug.h>
//#include "../../../../../EIRC5/src/libs/eirXfr/Debug.h"

GraphicsMainWindow::GraphicsMainWindow(const Qt::WindowStates ws, QWidget *parent)
    : QMainWindow(parent)
{
    TRACEQFI << ws << QOBJNAME(parent);
    setObjectName("GraphicsMainWindow");
}
