#pragma once
#include "eirType.h"

#include <QFile>

#include <QByteArray>

#include "QQFileInfo.h"

class EIRTYPE_EXPORT QQFile : public QFile
{
    Q_OBJECT
public:
    QQFile();

public: // static
    static QByteArray readAll(const QQFileInfo &fileInfo);
};

