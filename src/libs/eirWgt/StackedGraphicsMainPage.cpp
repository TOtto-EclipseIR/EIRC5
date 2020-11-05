#include "StackedGraphicsMainPage.h"

#include <eirXfr/Debug.h>

#include "StackedGraphicsMainWindow.h"

StackedGraphicsMainPage::StackedGraphicsMainPage(const MultiName &name, StackedGraphicsMainWindow *mainwin)
    : QWidget(mainwin)
    , mpMainWindow(mainwin)
{
    TRACEQFI << QOBJNAME(mainwin);
    setObjectName("StackedGraphicsMainPage:"+name());
}
