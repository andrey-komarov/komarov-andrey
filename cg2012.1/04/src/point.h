#ifndef pointH
#define pointH

#include <ostream>

struct point
{
    point();
    point(double x, double y);

    bool operator==(const point&) const;

    double x, y;
};

std::ostream& operator<<(std::ostream&, const point&);

#endif
