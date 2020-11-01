#pragma once

#include <QJsonValue>
#include <QJsonObject>

#include "MultiName.h"

class JsonItem : public QJsonValue
{
public:
    JsonItem();
    JsonItem(const MultiName &key, const QString &svalue);
    QJsonObject toObject() const;
    operator QJsonObject () const { return toObject(); }

private:
    MultiName mName;
};

