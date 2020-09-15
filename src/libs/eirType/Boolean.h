#pragma once


class Boolean
{
public:
    Boolean();
    Boolean(const bool is);
    bool isNull() const;
    bool isValid() const;
    bool isInvalid() const;
    bool is() const;
    operator bool () const;
    bool operator ()() const;

    bool set(const bool is=true, const bool valid=true);
    bool unset(const bool isNot=true);
    bool operator = (const bool is);
    void invalidate();
    void nullify();

private:
    bool mValid=false;
    bool mBool=false;
};

