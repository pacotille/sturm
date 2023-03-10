#pragma once

#include "num.hpp"

struct Rat {
    Num num, den;

    Rat(){}

    Rat(int num): num(num), den(1){}

    Rat(const Num &num): num(num), den(1){}

    Rat(const Num &num, const Num &den): num(num), den(den){
        reduce();
    }

    void reduce(){
        Num a = Num::gcd(num, den);
        if (a != 1){
            num /= a;
            den /= a;
        }
    }

    Rat inv() const {
        return Rat(den, num);
    }

    static Rat add(const Rat &a, const Rat &b){
        return Rat(a.num * b.den + a.den*b.num, a.den * b.den);
    }

    static Rat sub(const Rat &a, const Rat &b){
        return Rat(a.num * b.den - a.den*b.num, a.den * b.den);
    }

    static Rat mul(const Rat &a, const Rat &b){
        return Rat(a.num * b.num, a.den * b.den);
    }

    static Rat div(const Rat &a, const Rat &b){
        return Rat(a.num * b.den, a.den * b.num);
    }

    static int cmp(const Rat &a, const Rat &b){
        int result = Num::cmp(a.num * b.den, b.num * a.den);
        return b.den != a.den ? -result : result;
    }

    double to_double() const {
        return num.to_double() / den.to_double();
    }

    void print(std::vector<char> &c){
        num.print(c);
/*
std::string aux(c.begin(), c.end());
std::cout << aux << std::endl;
*/

        c.back() = '/';
std::vector<char> q;
        den.print(q);
c.insert(std::end(c), std::begin(q), std::end(q));

/*
std::string aux1(c.begin(), c.end());
std::cout << aux1 << std::endl;
*/

    }

    Rat& operator += (const Rat &b){ return *this = add(*this, b); }
    Rat& operator -= (const Rat &b){ return *this = sub(*this, b); }
    Rat& operator *= (const Rat &b){ return *this = mul(*this, b); }
    Rat& operator /= (const Rat &b){ return *this = div(*this, b); }

    bool operator == (const Rat &b) const { return cmp(*this, b) == 0; }
    bool operator != (const Rat &b) const { return cmp(*this, b) != 0; }
    bool operator <= (const Rat &b) const { return cmp(*this, b) <= 0; }
    bool operator >= (const Rat &b) const { return cmp(*this, b) >= 0; }
    bool operator <  (const Rat &b) const { return cmp(*this, b) <  0; }
    bool operator >  (const Rat &b) const { return cmp(*this, b) >  0; }

    Rat operator + (const Rat &b) const { return add(*this, b); }
    Rat operator - (const Rat &b) const { return sub(*this, b); }
    Rat operator * (const Rat &b) const { return mul(*this, b); }
    Rat operator / (const Rat &b) const { return div(*this, b); }
    Rat operator - (            ) const { return Rat(-num, den); }
};
