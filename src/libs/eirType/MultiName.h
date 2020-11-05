// file: ./libs/eirType/MultiName.h
#pragma once
#include "eirType.h"

#include <QByteArray>
#include <QChar>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "BasicName.h"
#include "QQStringList.h"

class EIRTYPE_EXPORT MultiName
{
public:
    typedef QList<MultiName> List;
    typedef QMap<MultiName /*sortable*/, QVariant> Map;

public:
    MultiName(void);
    MultiName(const QString & stringNames);
    MultiName(const char * cNames);
    MultiName(const QByteArray & baNames);
    MultiName(const BasicName &segment);
    MultiName(const BasicName::List & other);
    MultiName(const QStringList & qslNames);
    MultiName(const MultiName &base, const MultiName &name);
    bool isEmpty(void) const;
    bool notEmpty(void) const;
    void clear(void);
    void set(const QString & qsNames);
    void set(const QStringList & qslNames);
    void prependName(const MultiName &groupName);
    MultiName prepended(const MultiName &groupName) const;
    BasicName firstSegment() const;
    MultiName firstSegments(int count) const;
    BasicName segmentAt(const int index) const;
    MultiName appended(const BasicName &segment) const;
    bool startsWith(const MultiName &groupName) const;
    int segmentCount() const;
    void removeFirstSegments(int count);
    void removeLastSegment();
    BasicName lastSegment() const;
    MultiName firstSegmentsRemoved(int count) const;
    QStringList toStringList(void) const;
    QString toString(void) const;
    operator QString (void) const;
    QString operator () (void) const;
    QVariant toVariant(void) const;
    operator QVariant (void) const;
    static QQStringList stringList(const List mnames);
    QString sortable(void) const;
    uint hash() const;
    bool operator == (const MultiName & other) const;
    bool operator <  (const MultiName & other) const;
    void dump() const;

public:
    static QStringList toStringList(const List &mnl);
    static List toList(const QStringList &qsl);

protected:
    QString join(const QChar & delimiter) const;

protected: // static
    static QChar getDelimiter(void);
    static void setDelimiter(const QChar & value);

private:
    BasicName::List mBasicSegmentNames;

private: // static
    static const uint scmHashSeed;
    static QChar smDelimiter;
};

