//! \file FileInfoQueue.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QQueue>

#include "QQDirIterator.h"

class EIREXE_EXPORT FileInfoQueue : public QObject
{
    Q_OBJECT
public:
    explicit FileInfoQueue(QObject *parent = nullptr);
    int incomingCount() const;
    bool isIncomingEmpty() const;
    int pendingCount() const;
    bool isPendingEmpty() const;
    QFileInfo peekFirstPending() const;
    QFileInfo takeFirstPending();

public slots:
    void clearInput();
    void setMaxPending(const int max);
    void cancelPending();
    void append(const QFileInfo &fileInfo);
    void append(const QFileInfoList &fileInfoList);
    void processIncoming();

protected slots:

signals:
    void incomingEmpty();
    void pendingEmpty();
    void incomingAdded(QFileInfo fileInfo);
    void incomingTaken(QFileInfo fileInfo);
    void incomingProcessed(QFileInfo fileInfo);
    void enqueued(QFileInfo fileInfo);
    void dequeued(QFileInfo fileInfo);

private:
    QQueue<QFileInfo> mIncomingQueue;
    QQueue<QFileInfo> mPendingQueue;
    QQDirIterator mIncomingDirIterator;
    int mMaxPending = 1024;
    bool mPendingFull = false;
};

