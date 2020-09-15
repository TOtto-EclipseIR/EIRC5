#pragma once

#include <QObject>

#include <QList>
#include <QMultiMap>
#include <QRegularExpression>
#include <QString>
#include <QStringList>

#include <eirType/DualMap.h>
//#include <eirType/Id.h>

#include "ArgumentId.h"
#include "ArgumentItem.h"
#include "BaseArgumentHandler.h"

class ArgumentManager : public QObject
{
    Q_OBJECT
public:
    explicit ArgumentManager(QObject *parent = nullptr);
    ArgumentItem peek() const;
    ArgumentItem dequeue();
    int size() const;
    bool isEmpty() const;
    bool notEmpty() const;
    ArgumentId registerHandler(ArgumentId::List idsHandled,
                               BaseArgumentHandler * handler);

public slots:
    void enqueue(const ArgumentItem &item);
    void enqueue(const ArgumentItem::List &items);

signals:

private:
    QList<ArgumentItem> mItemList;
    DualMap<Uuid, BaseArgumentHandler> mUidHandlerDMap;
    QMultiMap<QRegularExpression /* trigger */, Uuid> mTriggerUidMMap;
};

