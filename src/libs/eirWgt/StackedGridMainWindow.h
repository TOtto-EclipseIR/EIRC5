#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QStackedLayout>
class QGridLayout;


class StackedGridMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StackedGridMainWindow(QWidget *parent = nullptr);
    QStackedLayout *stack()            { return mpStack; }
    QWidget *page(const int ix);
    QGridLayout *layout(const int ix);

signals:

private:
    QStackedLayout * mpStack=nullptr;

};

