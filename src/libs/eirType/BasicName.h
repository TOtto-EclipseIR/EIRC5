//! \file BasicName.h
#pragma once
#include "eirType.h"

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>

class EIRTYPE_EXPORT BasicName
{
public:
    typedef QByteArray Sortable;
    typedef QList<BasicName> List;

public:
    BasicName(void);
    BasicName(const QString & sNname);
    BasicName(const char * cName);
    BasicName(const QByteArray & baName);
    void set(const QString & name);
    bool isEmpty() const;
    bool notEmpty() const;
    void clear();
    QString fromBack(const QString &stuffAndName);
    QByteArray toByteArray() const;
    QString toString(void) const;
    operator QString (void) const;
    QString operator () (void) const;
    QVariant toVariant(void) const;
    operator QVariant (void) const;
    Sortable sortable(void) const;
    bool operator == (const BasicName & other) const;
    bool operator != (const BasicName & other) const;
    bool operator <  (const BasicName & other) const;
    bool UnitTest(void);

public: // static
    static bool isValidChar(const QChar &sChar);
    static QStringList toStringList(BasicName::List basicList);
    static BasicName::List listFrom(QString &names);
    static BasicName::List listFrom(const QStringList &names);

private:
    QString mName;
};
