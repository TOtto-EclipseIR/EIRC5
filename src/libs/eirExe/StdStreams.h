#pragma once

#include <QObject>

class QTextStream;

class StdStreams : public QObject
{
    Q_OBJECT
public:
    explicit StdStreams(QObject *parent = nullptr);
    QTextStream * in();
    QTextStream * out();
    QTextStream * err();

signals:

private:
    QTextStream * mpStdin=nullptr;
    QTextStream * mpStdout=nullptr;
    QTextStream * mpStderr=nullptr;

};

