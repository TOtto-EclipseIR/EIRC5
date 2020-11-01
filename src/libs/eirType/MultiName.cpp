// file: ./Library/Base/MultiName.cpp
#include "MultiName.h"

#include <eirXfr/Debug.h>

// static
const uint MultiName::scmHashSeed = *((uint *)("MultNameHashSeed"));
QChar MultiName::smDelimiter('/');

/*! \class MultiName
 *  \brief The MultiName class provides a multi-element name.
 *  \sa BasicName
 *  \sa Type Library
 *  \sa PersonName
 *  \note This and the BasicName class provide variable-type
 *      names, not intended for names of people.
 *      See (eventually) the PersonName class in the
 *      Type (TBD?) library for that use.
 *  \since v1.01
 */

/*!
 * \brief MultiName::MultiName() constructs an empty name.
 *
 * \since v1.01
 */
MultiName::MultiName(void) {;}

MultiName::MultiName(const QString & qsNames)
{
    set(qsNames);
}

MultiName::MultiName(const char *cNames)
{
    set(QString::fromLocal8Bit(cNames));
}

MultiName::MultiName(const QByteArray &baNames)
{
    set(QString::fromLocal8Bit(baNames));
}

MultiName::MultiName(const BasicName &segment)
{
    mBasicSegmentNames << segment;
}

MultiName::MultiName(const BasicName::List & other)
{
    mBasicSegmentNames = other;
}

MultiName::MultiName(const MultiName &base, const MultiName &name)
{
    mBasicSegmentNames = base.mBasicSegmentNames
                       + name.mBasicSegmentNames;
}

bool MultiName::isEmpty() const
{
    return mBasicSegmentNames.isEmpty();
}

bool MultiName::notEmpty() const
{
    return  ! isEmpty();
}

void MultiName::clear()
{
    mBasicSegmentNames.clear();
}

void MultiName::set(const QString & qsNames)
{
    clear();
    QString qs = qsNames.simplified();
    qs.replace(' ', smDelimiter);
    QStringList qsl = qs.split(smDelimiter, Qt::SkipEmptyParts);
    set(qsl);
}

void MultiName::set(const QStringList & qslNames)
{
    foreach(QString s, qslNames)
        mBasicSegmentNames << BasicName(s);
}

void MultiName::prependName(const MultiName &groupName)
{
    if ( ! groupName.isEmpty())
    {
        BasicName::List resultNames;
        resultNames << groupName.mBasicSegmentNames;
        resultNames << mBasicSegmentNames;
        mBasicSegmentNames = resultNames;
    }
}

MultiName MultiName::prepended(const MultiName &groupName) const
{
    BasicName::List resultNames;
    resultNames << groupName.mBasicSegmentNames;
    resultNames << mBasicSegmentNames;
    return resultNames;
}

BasicName MultiName::firstSegment() const
{
    return mBasicSegmentNames.first();
}

MultiName MultiName::firstSegments(int count) const
{
    MultiName result;
    for (int x = 0; x < qMin(count, segmentCount()); ++x)
        result.mBasicSegmentNames.append(segmentAt(x));
    return result;
}

BasicName MultiName::segmentAt(const int index) const
{
    return mBasicSegmentNames.at(index);
}

MultiName MultiName::appended(const BasicName &segment) const
{
    TRACEQFI << segment() << toString();
    MultiName result = *this;
    result.mBasicSegmentNames.append(segment);
    TRACEFNR(result.toString());
    return result;
}
/*
MultiName &MultiName::append(const BasicName &segment)
{
    TRACEQFI << segment() << "append() to" << toString();
    TRACE << BasicName::toStringList(mBasicSegmentNames);
    mBasicSegmentNames.append(segment);
    TRACE << BasicName::toStringList(mBasicSegmentNames);
    TRACE << toString();
    return *this;
}
*/
int MultiName::segmentCount() const
{
    return mBasicSegmentNames.size();
}

void MultiName::removeFirstSegments(int count)
{
    while (count--)
        mBasicSegmentNames.removeFirst();
}

void MultiName::removeLastSegment()
{
    mBasicSegmentNames.removeLast();
}

BasicName MultiName::lastSegment() const
{
    return mBasicSegmentNames.last();
}

MultiName MultiName::firstSegmentsRemoved(int count) const
{
    MultiName resultName(mBasicSegmentNames);
    resultName.removeFirstSegments(count);
    return resultName;
}

QStringList MultiName::toStringList() const
{
    QStringList qsl;
    foreach(BasicName bn, mBasicSegmentNames)
        qsl << bn.toString();
    return  qsl;
}

QString MultiName::toString() const
{
    return join(getDelimiter());
}

QString MultiName::operator ()(void) const
{
    return toString();
}

QVariant MultiName::toVariant() const
{
    return QVariant(toStringList());
}

QQStringList MultiName::stringList(const MultiName::List mnames)
{
    QQStringList rtn;
    foreach (MultiName mname, mnames) rtn << mname.toString();
    return rtn;
}

QString MultiName::sortable() const
{
    return toString().toLower();
}

uint MultiName::hash() const
{
    return qHash(sortable(), scmHashSeed);
}

bool MultiName::operator == (const MultiName & other) const
{
    return sortable() == other.sortable();
}

bool MultiName::operator < (const MultiName & other) const
{
    return sortable() < other.sortable();
}
/*
MultiName &MultiName::operator +=(const BasicName &segment)
{
    return append(segment);
}
*/
void MultiName::dump() const
{
    DUMP << toString();
}

// static
QStringList MultiName::toStringList(const List &mnl)
{
    QStringList qsl;
    foreach (MultiName mn, mnl) qsl << mn.toString();
    return qsl;
}

// static
MultiName::List MultiName::toList(const QStringList &qsl)
{
    List mnl;
    foreach (QString qs, qsl) mnl << MultiName(qs);
    return mnl;
}

// protected
QString MultiName::join(const QChar & delimiter) const
{
    QString qs;
    if ( ! isEmpty())
    {
        const QString sDelim(delimiter);
        BasicName::List copy = mBasicSegmentNames;
        qs = copy.takeFirst();
        while ( ! copy.isEmpty())
            qs += sDelim + copy.takeFirst().toString();
    }
    return qs;
}

bool MultiName::startsWith(const MultiName &groupName) const
{
    int n = groupName.segmentCount();
    for (int index = 0; index < n; ++index)
        if (segmentAt(index) != groupName.segmentAt(index))
            return false;
    return true;
}

QChar MultiName::getDelimiter(void) // static
{
    return smDelimiter;
}

void MultiName::setDelimiter(const QChar & value) // static
{
    smDelimiter = value;
}

MultiName::operator QVariant() const
{
    return toVariant();
}

MultiName::operator QString() const
{
    return toString();
}

