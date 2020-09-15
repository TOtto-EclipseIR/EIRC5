#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include <eirType/BasicName.h>
#include <eirType/BitFlags.h>

class FunctionInfo
{
public:
    class Parameter
    {
    public:
        typedef QList <Parameter> List;

    public:
        Parameter();
        Parameter(const QString &params,
                  const int index);
        Parameter(const QString &type,
                  const BasicName &name=BasicName(),
                  const QVariant &value=QVariant(),
                  const QString &defaultValue=QString());
        QString type() const;
        QString name() const;
        QString value() const;
        QString defaultValue() const;

    private:
        QString mType;
        BasicName mName;
        QVariant mValue;
        QString mDefaultValue;
    }; // Parameter sub-class

public:
    FunctionInfo();
    FunctionInfo(const QString &qFnInfo);
    void parse(const QString &qFnInfo);
    void clear();
    bool isEmpty() const;

private:
    void parse();
    void parseClear();

private:
    QString mQFuncInfoMacro;
    QString mPreModifier;
    BasicName mReturnType;
    BasicName mNameSpace;
    BasicName mClassName;
    BasicName mFunctionName;
    Parameter::List mParameterList;
    QString mPostModifier;
    BitFlags mFlags;
};

