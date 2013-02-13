#ifndef POINT_H
#define POINT_H
#include <ostream>

#include <iostream>
using std::cerr;

#include <memory>
using std::shared_ptr;
using std::weak_ptr;

struct point
{
    double x, y;

    point();
    point(double x, double y);

    bool operator==(const point&) const;
    bool operator<(const point&) const;
};

std::ostream& operator<<(std::ostream&, const point&);

#endif

