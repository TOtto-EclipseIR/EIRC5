#include "FileInfoQueue.h"

#include <QDir>

#include <eirXfr/Debug.h>

FileInfoQueue::FileInfoQueue(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("FileInfoQueue");
    CONNECT(this, &FileInfoQueue::incomingAdded,
            this, &FileInfoQueue::processIncoming);
}

int FileInfoQueue::incomingCount() const
{
    return mIncomingQueue.size();
}

bool FileInfoQueue::isIncomingEmpty() const
{
    return ! incomingCount();
}

int FileInfoQueue::pendingCount() const
{
    return mPendingQueue.size();
}

bool FileInfoQueue::isPendingEmpty() const
{
    return ! pendingCount();
}

QFileInfo FileInfoQueue::peekFirstPending() const
{
    return mPendingQueue.first();
}

QFileInfo FileInfoQueue::takeFirstPending()
{
    TRACEQFI << peekFirstPending();
    return mPendingQueue.takeFirst();
}

void FileInfoQueue::clearInput()
{
    TRACEFN
    NEEDDO(it);
}

void FileInfoQueue::setMaxPending(const int max)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(max)
}

void FileInfoQueue::cancelPending()
{
    TRACEFN
    NEEDDO(it);
}

void FileInfoQueue::append(const QFileInfo &fileInfo)
{
    TRACEFN
#if 0
    WANTUSE(fileInfo)
    QDir inDir("/INDIface/INDIin/console");
    QFileInfoList files = inDir
            .entryInfoList(QDir::Files | QDir::Readable);
    mPendingQueue.append(files);
    TRACE << mPendingQueue;
#else
    TRACEQFI << fileInfo;
    if ( ! fileInfo.exists())           return;
    if ( ! fileInfo.isWritable())       return;

    NEEDDO(more);

    mIncomingQueue.enqueue(fileInfo);
    EMIT(incomingAdded(fileInfo));
#endif
}

void FileInfoQueue::append(const QFileInfoList &fileInfoList)
{
    TRACEFN
    foreach (QFileInfo qfi, fileInfoList) append(qfi);
}

void FileInfoQueue::processIncoming()
{
    TRACEFN
    // Change mPendingFull status as necessary
    if (mPendingFull
            && pendingCount() < mMaxPending - (mMaxPending >> 2))
    {
        mPendingFull = false;
    }
    else if ( ! mPendingFull && pendingCount() > mMaxPending)
    {
        mPendingFull = true;
    }

    // Is nothing to do at this time
    if (mPendingFull || isIncomingEmpty())
    {
        QTimer::singleShot(1000, this,
                           &FileInfoQueue::processIncoming);
        return;
    }
    // Take next from incoming
    QFileInfo qfi = mIncomingQueue.dequeue();
    TRACE << "emit" << "incomingTaken(qfi)" << qfi;
    emit incomingTaken(qfi);
    if (qfi.isFile())
    {
        mPendingQueue.enqueue(qfi);
        return;
    }
    if (qfi.isDir())
    {
        NEEDDO(startIterator)
        mIncomingDirIterator.start(qfi.dir());
        // fornow process all here
        while (mIncomingDirIterator.hasNext())
        {
            mIncomingDirIterator.goNext();
            mPendingQueue.enqueue(mIncomingDirIterator.fileInfo());
        }
    }
}
