#pragma once
#include "eirXfr.h"

#include <QSharedDataPointer>

#include <QFlags>
#include <QString>
#include <QStringList>

#include <eirType/DProperty.h>

#define XFRFUNCTIONINFO_DATAPROPS(TND) \
    TND(QString, PrettyFunction, QString()) \
    TND(QStringList, Prefixes, QStringList()) \
    TND(QStringList, Namespaces, QStringList()) \
    TND(QString, ClassName, QString()) \
    TND(QString, FunctionName, QString()) \
    TND(QStringList, ArgumentTypeNames, QStringList()) \
    TND(QStringList, ArgumentNames, QStringList()) \
    TND(QStringList, Suffixes, QStringList()) \
    TND(QStringList, TemplateArgs, QStringList()) \

class XfrFunctionInfoData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(XFRFUNCTIONINFO_DATAPROPS)
public:
    XfrFunctionInfoData(void)
    {
        DEFINE_DATAPROPS_CTORS(XFRFUNCTIONINFO_DATAPROPS)
    }
};

class EIRXFR_EXPORT XfrFunctionInfo
{
    DECLARE_PARENT_DATAPROPS(XFRFUNCTIONINFO_DATAPROPS)
    DECLARE_DATAPROPS(XfrFunctionInfo, XfrFunctionInfoData)
public:
    enum Flag
    {
        NoFlag          = 0,
        PrefixConst     = 0x00000001,
        Static          = 0x00000002,
        Volatile        = 0x00000004,
    };
    Q_DECLARE_FLAGS(Flaga, Flag);

public:
    XfrFunctionInfo(const char * qFuncInfo);
    void parse();

private:
    const QString cmQfiString;
    QStringList mElements;
};
