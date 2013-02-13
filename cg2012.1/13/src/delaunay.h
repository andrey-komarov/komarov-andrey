#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "point.h"
#include <vector>
using std::vector;
#include <ostream>
using std::ostream;

struct triangle
{
    point points[3];
    triangle (const point& p1, const point& p2, const point& p3);
};

ostream& operator<<(ostream& out, const triangle& t);

vector<triangle> triangulate(const vector<point>&);


#endif
