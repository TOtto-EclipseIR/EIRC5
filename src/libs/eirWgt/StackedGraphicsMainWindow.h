#pragma once
#include "eirWgt.h"

#include <QMainWindow>

#include <QMap>
class QGraphicsScene;
class QGraphicsView;
class QStackedWidget;

#include <eirType/MultiName.h>

class StackedGraphicsMainPage;

class EIRWGT_EXPORT StackedGraphicsMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StackedGraphicsMainWindow(const Qt::WindowStates ws=Qt::WindowMaximized);
    QStackedWidget * mainStackWidget()      { return mpMainStackWidget; }
    QGraphicsScene * scene()                { return mpGraphicsScene; }
    QGraphicsView * view()                  { return mpGraphicsView; }

    StackedGraphicsMainPage *addPage(const MultiName &name);


signals:
    void constructed();

public slots:
    void initialize();

private slots:

private:
    QStackedWidget * mpMainStackWidget=nullptr;
    QGraphicsScene * mpGraphicsScene=nullptr;
    QGraphicsView * mpGraphicsView=nullptr;
    QMap<MultiName, StackedGraphicsMainPage *> mNamePageMap;
};

