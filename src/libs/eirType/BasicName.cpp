#include "BasicName.h"

#include <QChar>
#include <QRegularExpression>

#include <eirXfr/Debug.h>

/*! \class BasicName
 *  \brief The BasicName class provides a single-element name.
 *  \sa MultiName
 *  \sa Type Library
 *  \sa PersonName
 *  \note This and the MultiName class provide variable-type
 *      names, not intended for names of people.
 *      See (eventually) the PersonName class in the
 *      Type (TBD?) library for that use.
 *  \since v1.00
 */

/*!
 * \brief BasicName::BasicName constructs an empty name.
 *
 * \since v1.01
 */
BasicName::BasicName(void) : mName(QString()) {;}

/*!
 * \brief BasicName::BasicName constructs a name from a QString().
 * \param sName is the initial name.
 * \since v1.00
 */
BasicName::BasicName(const QString & sName)
{
    set(sName);
}

/*!
 * \brief BasicName::BasicName constructs a name
 *      from a null-terminated character string.
 * \param cName is the initial name
 * \since v1.02
 */
BasicName::BasicName(const char *cName)
{
    set(QString::fromLocal8Bit(cName));
}

/*!
 * \brief BasicName::BasicName constructs a name from a QByteArray().
 * \param ba contains the initial name.
 * \since v1.01
 */
BasicName::BasicName(const QByteArray & ba)
{
    set(QString::fromLocal8Bit(ba.data()));
}

/*!
 * \brief BasicName::set sets a new name
 * \param name is a QString() containing the new name.
 * \since v1.00
 * \todo Parse the input string for valid name characters.
 */
void BasicName::set(const QString &name)
{
//    LIKEDO("static Valid chars; hint: _ is empty or root")
    mName = name;
}

bool BasicName::isEmpty() const
{
    return mName.isEmpty();
}

bool BasicName::notEmpty() const
{
    return ! isEmpty();
}

void BasicName::clear()
{
    mName.clear();
}

QString BasicName::fromBack(const QString &stuffAndName)
{
    TRACEQFI << stuffAndName;
    MUSTDO(why);
    int ix;
    mName.clear();
    for (ix = stuffAndName.size()-1; ix > 0; --ix)
    {
        QChar qch = stuffAndName[ix];
        bool valid = isValidChar(qch);
        TRACE << ix << qch << valid;
        if (valid)
            mName.prepend(qch);
        else
            break;                                  /* /--------\ */
    }
    return stuffAndName.left(ix);
}

/*!
 * \brief BasicName::toString returns the string.
 * \return the stored QString()
 * \since v1.00
 */
QString BasicName::toString(void) const
{
    return mName;
}

QByteArray BasicName::toByteArray() const
{
    return mName.toLocal8Bit();
}

/*!
 * \brief BasicName::operator QString convenience
 *      cast access to toString().
 * \return the stored QString().
 * \since v1.01
 */
BasicName::operator QString(void) const
{
    return toString();
}

/*!
 * \brief BasicName::operator () convenience
 *      operator access to toString().
 * \return the stored QString().
 * \since v1.01
 */
QString BasicName::operator () (void) const
{
    return toString();
}

/*!
 * \brief BasicName::toVariant creates a string-valued QVariant().
 * \return the QVariant().
 * \since v1.02
 */
QVariant BasicName::toVariant(void) const
{
    return QVariant(toString());
}

/*!
 * \brief BasicName::operator QVariant convenience cast
 *      access to toVariant().
 * \return the QVariant().
 * \since v1.02
 */
inline BasicName::operator QVariant(void) const
{
    return toVariant();
}

/*!
 * \brief BasicName::sortable
 * \return a sortable QByteArray().
 * \since v1.01
 * \internal
 */
BasicName::Sortable BasicName::sortable(void) const
{
    return toByteArray().toLower();
}

/*!
 * \brief BasicName::operator== compares stored string
 *      to another instance.
 * \return true if the sortable strings are equal.
 * \since v1.01
 */
bool BasicName::operator == (const BasicName & other) const
{
    return sortable() == other.sortable();
}

bool BasicName::operator !=(const BasicName &other) const
{
    return sortable() != other.sortable();
}

/*!
 * \brief BasicName::operator< compares stored string
 *      to another instance.
 * \param the right hand side
 * \return true if this sortable string is less than the other.
 * \since v1.01
 */
bool BasicName::operator <  (const BasicName &other) const
{
    return sortable() < other.sortable();
}

// static
bool BasicName::isValidChar(const QChar &sChar)
{
    WANTDO(More than space)
    return (' ' == sChar);
}

/*!
 * \brief static BasicName::toStringList
 *      converts a list if BasicName entries to a list of QStrings.
 * \param basicList input list of BasicName items
 * \return QStringList list converted to QStrings
 *
 */

QStringList BasicName::toStringList(BasicName::List basicList)
{
    QStringList stringNames;
    foreach(BasicName basicName, basicList)
        stringNames << basicName.toString();
    return stringNames;

}

BasicName::List BasicName::listFrom(const QStringList &names)
{
    BasicName::List basicNameList;
    foreach (QString name, names)
        basicNameList << BasicName(name);
    return basicNameList;
}

// static
BasicName::List BasicName::listFrom(QString &names)
{
    TRACEQFI << names;
    names.replace(QRegularExpression("[,;]"), " ");
    QStringList nameList = names.simplified().split(' ');
    return listFrom(nameList);
}
