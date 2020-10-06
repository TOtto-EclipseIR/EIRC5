#pragma once
#include "eirQtCV.h"


class cvBGRA
{
public:
    cvBGRA();
    cvBGRA(const quint32 u32);
    cvBGRA(quint8 * ptr);
    void set(const cvBGRA other);
    quint8 red() const;
    quint8 grn() const;
    quint8 blu() const;
    quint8 alf() const;
    quint32 u32() const;
    bool isGrey() const;
    bool isGreyish(signed epsilon=2) const;

private:
    quint32 mU32;
};

