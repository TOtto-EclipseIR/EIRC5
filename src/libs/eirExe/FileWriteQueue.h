#pragma once

#include <QObject>

#include <QByteArray>
#include <QQueue>
#include <QMap>
#include <QString>

class FileWriteQueue : public QObject
{
    Q_OBJECT

public:
    class Item
    {
    public:
        Item();
        Item(const QString &fileName, const QByteArray &bytes);
        QString fileName() const;
        QByteArray bytes() const;
        bool isNull() const;
        QString operator () () const;

    private:
        QString mFileName;
        QByteArray mBytes;
    }; // subclass Item
public:
    explicit FileWriteQueue(QObject *parent = nullptr);

protected:
    Item takeFirst();

public slots:
    void enqueue(const Item &item);

protected slots:
    void resume();
    void pause();
    void deqNext();
    void write(Item item);

signals:
    void enqueued();
    void enqueued(QString fileName);
    void enqueued(Item item);
    void enqueued(int count);
    void dequeued();
    void dequeued(QString fileName);
    void dequeued(Item item);
    void dequeued(int count);
    void resumed();
    void paused();

private:
    QQueue<Item> mItemQueue;
    bool mDequing=false;

};

