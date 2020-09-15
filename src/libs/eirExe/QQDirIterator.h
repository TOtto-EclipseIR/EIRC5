// file: {repo: EIRC2}./src/libs/eirExe/QQDirIterator.h
#pragma once

#include <QDirIterator>
#include <QFileInfo>

class QQDirIterator
{
public:
    QQDirIterator();
    bool isNull() const;
    bool notNull() const;
    void nullify();

    bool start(const QDir &dir);
    bool hasNext() const;
    void goNext();
    QFileInfo fileInfo() const;

private:
    QDirIterator * mpDirIterator=nullptr;
};

