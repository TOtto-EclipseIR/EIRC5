#include "QQStringList.h"

#include <eirXfr/Debug.h>


QQStringList::QQStringList() {;}

QQStringList::QQStringList(const QStringList &other)
{
    TRACEQFI << other;
    foreach (QString s, other) append(QQString(s));
}

void QQStringList::prepend(const QQStringList &other)
{
    TRACEQFI << other;
    QList<QQString>::reverse_iterator i = rbegin();
    while (i != rend()) QQString::List::prepend(*i);
}

QQString QQStringList::join(const QQString &separator) const
{
    TRACEQFI << separator;
    if (isEmpty()) return QQString();           /* /========\ */
    QQStringList copy = *this;
    QQString joined = copy.takeFirst();
    while ( ! copy.isEmpty()) joined += separator + copy.takeFirst();
    return joined;
}

bool QQStringList::notEmpty() const
{
    return ! isEmpty();
}
