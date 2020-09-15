// file: {EIRC2 repo}./src/libs/eirTypes/Enumeration.cpp

#include "Enumeration.h"

#include <QStringList>

#include <eirXfr/Debug.h>

/*! Enumeration Construct an empty, invalid item */
Enumeration::Enumeration(void)
    : value_i(0)
    , name_s("[null]")
    , name_map(0)
{
}

/*! Construct an item from a valid integer

    @arg    const int value a valid integer
    @note   if the specified value is not valid, an invalid item is constructed

*/
Enumeration::Enumeration(Named<int> * p,
                         const int value)
    : value_i(value)
    , name_map(p)
{
}

Enumeration::Enumeration(Named<int> * p,
                         const QString & name)
    : value_i(0)
    , name_map(p)
{
    set(name);
}

Enumeration::Enumeration(const Enumeration & other)
    : value_i(other.value_i)
    , name_s(other.name_s)
    , name_map(other.name_map)
{
}

Enumeration & Enumeration::operator = (const Enumeration & other)
{
    value_i = other.value_i, name_s = other.name_s, name_map = other.name_map;
//    TRACEFN
  //  TRACE << value_i << name_s;
    return *this;
}

bool Enumeration::isEmpty(void) const
{
    return name_map ? name_map->isEmpty() : true;
}

Enumeration Enumeration::first(void) const
{
//    TRACEFN
  //  TRACE << (isEmpty() ? Enumeration() : Enumeration(name_map, name_map->first(1))).name();
    return isEmpty() ? Enumeration() : Enumeration(name_map, name_map->first(1));
}

Enumeration Enumeration::last(void) const
{
    return isEmpty() ? Enumeration() : Enumeration(name_map, name_map->last(1));
}

QString Enumeration::nameOf(const int value) const
{
//    TRACEQFI << value;
    QString result = name_map ? name_map->value(value) : QString();
  //  TRACEFNR(result);
    return result;
}

int Enumeration::valueOf(const QString & name) const
{
//    TRACEQFI << name;
    int result = name_map ? name_map->value(name) : 0;
  //  TRACEFNR(result);
    return result;
}

Enumeration & Enumeration::operator ++(void) // prefix ++e
{
//    TRACEFN
    if (name_map)
        set(name_map->next(value_i));
  //  TRACE << name();
    return *this;
}

Enumeration Enumeration::operator ++(int)  // postfix e++
{
//    TRACEFN
    Enumeration before(*this);
    if (name_map)
        set(name_map->next(value_i));
  //  TRACE << before.name();
    return before;
}

Enumeration & Enumeration::operator --(void) // prefix --e
{
//    TRACEFN
    if (name_map)
        set(name_map->previous(value_i));
  //  TRACE << name();
    return *this;
}

Enumeration Enumeration::operator --(int)  // postfix e--
{
//    TRACEFN
    Enumeration before(*this);
    if (name_map)
        set(name_map->previous(value_i));
  //  TRACE << before.name();
    return before;
}

void Enumeration::set(const int value)
{
    if (name_map && name_map->contains(value))
    {
        value_i = value;
        name_s = name_map->value(value_i);
    }
    else
        name_map = 0;

    if ( ! name_map)
    {
        value_i = 0;
        name_s.clear();
    }
}

void Enumeration::set(const QString & name)
{
    if (name_map && name_map->contains(name))
    {
        value_i = name_map->value(name);
        name_s = name_map->value(value_i);
    }
    else
        name_map = 0;

    if ( ! name_map)
    {
        value_i = 0;
        name_s.clear();
    }
}

void Enumeration::invalidate(void)
{
//    TRACEFN
    value_i = 0, name_s.clear(), name_map = 0;
}

bool Enumeration::isValid(void) const
{
//    TRACEFN
    bool result = name_map
            && (name_map->contains(value_i)
                || 0 == value_i);
  //  TRACEFNR(result);
    return result;
}

bool Enumeration::isNull(void) const
{
//    TRACEFN
    bool result = ! name_map;
  //  TRACEFNR(result);
    return result;
}

bool Enumeration::is(const int value) const
{
//    TRACEFN
  //  TRACE << value;
    bool result = isValid() && value_i == value;
//    TRACEFNR(result);
    return result;
}

bool Enumeration::operator == (const Enumeration & other) const
{
//    TRACEFN
  //  TRACE << other.value() << other.name();
    bool result = isValid()
            && other.isValid()
            && value_i == other.value_i;
    //TRACEFNR(result);
    return result;
}

bool Enumeration::operator < (const Enumeration & other) const
{
//    TRACEFN
  //  TRACE << other.value() << other.name();
    bool result = isValid()
            && other.isValid()
            && value_i < other.value_i;
    //TRACEFNR(result);
    return result;
}

int Enumeration::operator()() const
{
    return value();
}

Enumeration::operator int (void) const
{
    return value();
}

int Enumeration::value(void) const
{
    return value_i;
}

QString Enumeration::name(void) const
{
//    TRACEFN
  //  TRACEFNR(name_s);
    return name_s;
}

QList<Enumeration> Enumeration::all(void)
{
//    TRACEFN
    QList<Enumeration> result;
    foreach (int i, values())
        result.append(Enumeration(name_map, i));
    //TRACEFNR(result);
    return result;
}

QList<int> Enumeration::values(void) const
{
//    TRACEFN
    QList<int> result = name_map ? name_map->keys() : QList<int>();
//    TRACEFNR(result);
    return result;
}

QStringList Enumeration::nameFlags(int f)
{
//    TRACEFN
    QStringList nameList;
    if (name_map)
    {
        QList<int> intList = name_map->keys();
        foreach (int i, intList)
            if (i && i == (i & f))
                nameList << name_map->name(i);
    }
    //TRACEFNR(nameList);
    return nameList;
}

bool Enumeration::isValid(const QString & name)
{
    return (name_map && name_map->contains(name));
}

int Enumeration::value(const QString & name)
{
//    TRACEFN
  //  TRACE << name;
    int result = -1;
    if (name_map)
    {
        if (name_map->contains(name))
            result = name_map->value(name);
        else
            WARN << "Enumeration::value(%s) invalid" << name;
    }
    else
    {
       WARN << "Enumeration::value(%s) with no instance" << name;
    }
//    TRACEFNR(result);
    return result;
}

QList<Enumeration> Enumeration::parse(const QString & string)
{
//    TRACEQFI << string;
    QList<Enumeration> result;

    foreach (QString s, string.simplified()
                              .split(' ', Qt::SkipEmptyParts))
    {
        bool negate = false;
        bool toggle = false;
        if (s.startsWith('-'))
        {
            negate = true;
            s = s.mid(1);
        }
        else if (s.startsWith('!'))
        {
            toggle = true;
            s = s.mid(1);
        }

        if ("~" == s)
        {
            if (negate)
                result.clear();
            else
                result = all();
        }
        else if (s.contains('~'))
        {
            BEXPECT(isValid());
            Enumeration min_v(first());
            Enumeration max_v(last());
            if (s.startsWith('~'))
                max_v.set(s.mid(1));
            else if (s.endsWith('~'))
                min_v.set(s.left(s.size()-1));
            else
            {
                int x = s.indexOf('~');
                min_v.set(s.left(x));
                max_v.set(s.mid(x+1));
            }
            if (min_v.isValid() && max_v.isValid())
            {
                BEXPECT(isValid());
                Enumeration v(min_v);
                do
                {
                    if (negate)
                        result.removeAll(v);
                    else
                        result.append(v);
                    ++v;
                } while (v.isValid() && v <= max_v);
            }
        }
        else
        {
            BEXPECT(isValid());
            Enumeration v(first());
            v.set(s);
            if (v.isValid())
            {
                if (negate)
                    result.removeAll(v);
                else if (toggle)
                {
                    if (result.contains(v))
                        result.removeAll(v);
                    else
                        result.append(v);
                }
                else
                    result.append(v);
            }
            else
                WARN << "Enumeration(%s) invalid" << s;
        }
    }
//    TRACERTN(result)
    return result;
}

int Enumeration::parseFlags(const QString & string)
{
    int result = 0;
    QList<Enumeration> eList = parse(string);
    foreach (Enumeration e, eList)
        result |= e.value();
    return result;
}
