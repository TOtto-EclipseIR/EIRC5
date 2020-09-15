#pragma once

#include <QPair>

template <typename T> class MinMaxPair
{
public:
    MinMaxPair() {;}
    MinMaxPair(const T &minT, const T &maxT)
    { set(minT, maxT); }
    void clear() { set(T(), T()); }
    void set(const T &minT, const T &maxT)
    { mMinMaxPair.first=minT, mMinMaxPair.second=maxT; }
    T min() const { return mMinMaxPair.first; }
    T max() const { return mMinMaxPair.second; }

private:
    QPair<T,T> mMinMaxPair;
};
