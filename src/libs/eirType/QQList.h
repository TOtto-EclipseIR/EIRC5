#pragma once

#include <QList>

template<typename T> class QQList : public QList<T>
{
public:
    QQList<T>() : QList<T>() {;}
    QQList<T>(const QList<T> other) : QList<T>(other) {;}
    ~QQList<T>() {;}
    T at(const int ix)
    { while (size() < ix) append(T()); return QList<T>::at(ix); }
    void insert(const int ix, const T &value)
    { while (size() < ix) append(T()); return QList<T>::insert(ix, value); }
    void removeAt(const int ix)
    { if (ix < size()) QList<T>::removeAt(ix); }
    void replace(const int ix, const T &value)
    { while (size() < ix) append(T()); return QList<T>::replace(ix, value); }
    T takeAt(const int ix)
    { return (ix < size()) ? QList<T>::at(ix) : T(); }
    T &operator[](const int ix)
    { while (size() < ix) append(T()); return QList<T>::operator[](ix); }
    operator QList<T> () { return QList<T>(*this); }
};
