#pragma once
#include "eirXfr.h"

#include <QSharedDataPointer>

#include <QFlags>
#include <QString>
#include <QStringList>

#include <eirType/DProperty.h>

#define XFRFUNCTIONINFO_DATAPROPS(TND) \
    TND(QString, PrettyFunction, QString()) \
    TND(qint32, Flags, 0) \
    TND(QStringList, Prefixes, QStringList()) \
    TND(QStringList, Namespaces, QStringList()) \
    TND(QString, ClassName, QString()) \
    TND(QString, FunctionName, QString()) \
    TND(QString, ArgumentTypeNames, QString()) \
    TND(int, ArgumentCount, 0) \
    TND(QStringList, ArgumentNameList, QStringList()) \
    TND(QStringList, Suffixes, QStringList()) \
    TND(QString, TemplateWith, QString()) \
    TND(QString, ReturnType, QString()) \

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
        ReturnsConst    = 0x01000000,
        Static          = 0x02000000,
        Volatile        = 0x04000000,
        ReturnsVoid     = 0x08000000,
        ReturnsBool     = 0x10000000,
        CDecl           = 0x40000000,

        VoidArgument    = 0x00001000,

        ConstFunction   = 0x00000001,
        HasTemplateInfo = 0x00000002,
        PureVirtual     = 0x00000004,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

public:
    XfrFunctionInfo(const char * qFuncInfo);
    void clear();
    bool isNull() const;
    bool setArgumentNames(const QStringList argNames);
    bool setArgumentName(const int index, const QStringList argNames);
    bool isFlag(const Flags flags) const;
    bool argumentCount() const;


private:
    void parse();
    void parseArguments();
    void parseClassFunctionNames();
    void parsePrefix();
    void parseSuffix();
    void orFlag(const Flags flags);
    bool findAndRemove(const QString &target, const int beforePos=INT_MAX);

private:
    const QString cmQfiString;
    QString mWorkingQfi;
    QStringList mElements;
};
