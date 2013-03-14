#ifndef vizibility_h
#define vizibility_h

#include "point.h"
#include <ostream>
#include <vector>
using std::vector;

struct segment
{
    point a, b;

    segment(const point& a, const point& b);

    bool operator==(const segment&) const;
};

std::ostream& operator<<(std::ostream& out, const segment& s);

vector<point> visible(vector<segment>, const point&);

#endif
