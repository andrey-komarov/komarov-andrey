#include "mincircle.h"
#include "predicates.h"

#include <algorithm>
using std::random_shuffle;

circle::circle(const point& p1, const point& p2)
    : n(2)
{
    p[0] = p1;
    p[1] = p2;
}

circle::circle(const point& p1, const point& p2, const point& p3)
    : n(3)
{
    if (turn(p1, p2, p3) == Sign::LEFT)
    {
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
    } 
    else
    {
        p[0] = p1;
        p[2] = p2;
        p[1] = p3;
    }
}

std::ostream& operator<<(std::ostream& out, const circle& c)
{
    if (c.n == 2)
    {
        return out << "Diameter{" << c.p[0] << "--" << c.p[1] << "}";
    }
    else
    {
        return out << "Tri{" << c.p[0] << "--" << c.p[1] << "--" << c.p[2] << "}";
    }
}

bool notin(const point& p, const circle& c)
{
    if (c.n == 2)
        return incircle(c.p[0], c.p[1], p) == Sign::OUTSIDE;
    else
        return incircle(c.p[0], c.p[1], c.p[2], p) == Sign::OUTSIDE;
}

template<typename Iter>
circle rebuild2(Iter be, Iter en, const point& p, const point& q)
{
    circle c(p, q);
    for (; be != en; be++)
        if (notin(*be, c))
            c = circle(p, q, *be);
    return c;
}

template<typename Iter>
circle rebuild(Iter be, Iter en, const point& p)
{
    random_shuffle(be, en);
    circle c(*be, p);
    Iter it = be;
    it++;
    for ( ; it != en; it++)
        if (notin(*it, c))
            c = rebuild2(be, it, *it, p);
    return c;
}

circle minimalCoveringCircle(std::vector<point> p)
{
    random_shuffle(p.begin(), p.end());
    circle c(p[0], p[1]);
    for (size_t i = 2; i < p.size(); i++)
        if (notin(p[i], c))
            c = rebuild(p.begin(), p.begin() + i, p[i]);
    return c;
}
