#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

using std::istream;
using std::ostream;
using std::string;
using std::max;

const long long base = 1000000000;
const int base_length = 9;

class longint
{	
	long long* a;
	size_t len;
	
	//~ longint(long long*& b, size_t len);
	longint(long long*&, size_t);
	void norm();
	void norm(long long*& a, size_t&) const;
	long long operator[](int pos) const;
	
	public:
	longint(){};
	longint(int);
	bool operator>(const longint&) const;
	bool operator<(const longint&) const;
	bool operator>=(const longint&) const;
	bool operator<=(const longint&) const;
	bool operator==(const longint&) const;
	bool operator!=(const longint&) const;
	longint& operator=(const longint&);
	longint operator+(const longint&) const;
	longint operator-(const longint&) const;
	longint operator*(const longint&) const;
	longint operator*(const long long&) const;
	longint operator/(const long long&) const;
	longint operator/(const longint&) const;
	longint operator<<(const size_t) const;
	
	friend istream& operator>>(istream&, longint&);
	friend ostream& operator<<(ostream&, const longint&);
	
};

#include "long.cpp"
