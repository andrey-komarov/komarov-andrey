#include "point.h"

point::point()
{}

point::point(double x, double y) :
    x(x), y(y)
{}

bool point::operator==(const point& p) const
{
    return x == p.x && y == p.y;
};

bool point::operator<(const point& p) const
{
    if (x != p.x)
        return x < p.x;
    return y < p.y;
}

std::ostream& operator<<(std::ostream& out, const point& p)
{
    return out << "(" << p.x << ", " << p.y << ")";
}
