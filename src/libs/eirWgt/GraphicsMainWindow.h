#pragma once

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>

class GraphicsMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GraphicsMainWindow(const Qt::WindowStates ws=Qt::WindowMaximized,
                                QWidget *parent = nullptr);
    QGraphicsScene * scene()        { return mpScene; }
    QGraphicsView * view()          { return mpView; }

signals:

private:
    QGraphicsScene * mpScene=nullptr;
    QGraphicsView * mpView=nullptr;
};

