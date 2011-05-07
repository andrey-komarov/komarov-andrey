#ifndef big_intH
#define big_intH

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "container.h"

using std::istream;
using std::ostream;
using std::string;
using std::max;

const digit_t base = 100000000;
const size_t base_length = 8;

struct big_int
{
	big_int();
    big_int(digit_t);
    big_int(const big_int&);
    void swap(big_int&);
    void swap(big_int& a, big_int& b);
    bool operator==(const big_int&) const;
    bool operator>(const big_int&) const;
    big_int& operator+=(const big_int&);
    big_int& operator*=(const digit_t&);
    big_int& operator*=(const big_int&);
    big_int& operator/=(const digit_t&);
    big_int& operator/=(big_int);
    big_int& operator%=(const big_int&);

private:
    container a;
    size_t len;
    bool negative;

    big_int(const container&, size_t);
    void norm();
    void norm(container& a, size_t&) const;
    big_int operator<<(const size_t) const;

    friend istream& operator>>(istream&, big_int&);
	friend ostream& operator<<(ostream&, const big_int&);
	friend big_int operator-(big_int);
	friend big_int abs(big_int a);
};

big_int abs(big_int a);

bool operator<(const big_int&, const big_int&);
bool operator<=(const big_int&, const big_int&);
bool operator>=(const big_int&, const big_int&);
bool operator!=(const big_int&, const big_int&);

big_int& operator-=(big_int&, const big_int&);
big_int operator-(big_int, const big_int&);
big_int operator+(big_int, const big_int&);
big_int operator*(big_int, const digit_t&);
big_int operator*(big_int, const big_int &);
big_int operator/(big_int, const digit_t&);
big_int operator/(big_int, const big_int&);
big_int operator%(big_int, const big_int&);

#include "big_int.cpp"

#endif /* big_intH */
