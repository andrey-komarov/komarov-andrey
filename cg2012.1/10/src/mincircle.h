#ifndef mincircle_h
#define mincircle_h

#include "point.h"
#include <ostream>
#include <vector>
using std::vector;

struct circle
{
    int n;
    point p[3];

    circle(const point&, const point&);
    circle(const point&, const point&, const point&);
};

std::ostream& operator<<(std::ostream& out, const circle&);

circle minimalCoveringCircle(vector<point> p);

#endif
