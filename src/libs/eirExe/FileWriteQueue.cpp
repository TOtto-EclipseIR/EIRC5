#include "FileWriteQueue.h"

#include <QFile>
#include <QTimer>

#include <eirXfr/Debug.h>

FileWriteQueue::FileWriteQueue(QObject *parent) : QObject(parent)
{
    TRACEFN
    setObjectName("FileWriteQueue");
    CONNECT(this, SIGNAL(dequeued(Item)),
            this, SLOT(write(Item)));
}

FileWriteQueue::Item FileWriteQueue::takeFirst()
{
    TRACEQFI << mItemQueue.size();
    Item item;
    if (mItemQueue.isEmpty())
    {
        EMIT(dequeued(mItemQueue.size()));
        pause();
    }
    else
    {
        item = mItemQueue.dequeue();
        EMIT(dequeued());
        EMIT(dequeued(item.fileName()));
        EMIT(dequeued(item));
        EMIT(dequeued(mItemQueue.size()));
        QTimer::singleShot(100, this, &FileWriteQueue::deqNext);
    }
    return item;
}

void FileWriteQueue::enqueue(const FileWriteQueue::Item &item)
{
    TRACEFN
    mItemQueue.enqueue(item);
    EMIT(enqueued());
    EMIT(enqueued(item.fileName()));
    EMIT(enqueued(item));
    EMIT(enqueued(mItemQueue.size()));
}

void FileWriteQueue::resume()
{
    TRACEFN
    if ( ! mDequing)
    {
        mDequing = true;
        EMIT(resumed());
        QTimer::singleShot(100, this, &FileWriteQueue::deqNext);
    }
}

void FileWriteQueue::pause()
{
    TRACEFN
    if (mDequing)
    {
        mDequing = false;
        EMIT(paused());
    }
}

void FileWriteQueue::deqNext()
{
    TRACEFN
    if (mItemQueue.size())
    {
        takeFirst();
        QTimer::singleShot(100, this, &FileWriteQueue::deqNext);
    }
    else
    {
        EMIT(dequeued(mItemQueue.size()));
        pause();
    }
}

void FileWriteQueue::write(FileWriteQueue::Item item)
{
    TRACEQFI << item();
    QFile file(item.fileName(), this);
    EXPECT(file.open(QIODevice::WriteOnly
                      | QIODevice::Truncate));
    EXPECT(file.write(item.bytes()));
}

FileWriteQueue::Item::Item()
{
    TRACEFN
}

FileWriteQueue::Item::Item(const QString &fileName,
                           const QByteArray &bytes)
    : mFileName(fileName)
    , mBytes(bytes)
{
    TRACEQFI << fileName << bytes.size();
}

QString FileWriteQueue::Item::fileName() const
{
    return mFileName;
}

QByteArray FileWriteQueue::Item::bytes() const
{
    return mBytes;
}

bool FileWriteQueue::Item::isNull() const
{
    return mFileName.isEmpty() || mBytes.isEmpty();
}

QString FileWriteQueue::Item::operator ()() const
{
    return isNull()
        ? "Null FileWriteQueue::Item"
        : QString("%1 %2 bytes").arg(fileName())
                                .arg(bytes().size());
}
