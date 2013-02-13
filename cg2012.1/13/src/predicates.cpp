#include "predicates.h"

#include <gmpxx.h>

#include <limits>
using std::numeric_limits;
#include <cmath>
using std::abs;

Sign turnDouble(const point& a, const point& b, const point& c)
{
    double ax = a.x;
    double ay = a.y;
    double bx = b.x;
    double by = b.y;
    double cx = c.x;
    double cy = c.y;
    double s1 = (bx - ax) * (cy - ay);
    double s2 = (cx - ax) * (by - ay);
    double det = s1 - s2;
    double meps = numeric_limits<double>::epsilon() * 8;
    double eps = meps * (abs(s1) + abs(s2));
    if (abs(det) < eps)
        return Sign::ON;
    else if (det < 0)
        return Sign::RIGHT;
    else 
        return Sign::LEFT;
}

Sign turn(const point& a, const point& b, const point& c)
{
    Sign s = turnDouble(a, b, c);
    if (s != Sign::ON)
        return s;
    mpq_class ax = a.x;
    mpq_class ay = a.y;
    mpq_class bx = b.x;
    mpq_class by = b.y;
    mpq_class cx = c.x;
    mpq_class cy = c.y;
    mpq_class det = (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
    if (det == 0)
        return Sign::ON;
    else if (det < 0)
        return Sign::RIGHT;
    else 
        return Sign::LEFT;
}

Sign incircleShewchuckOriginal(const point& a, const point& b, const point& c, const point& d)
{
  double adx, bdx, cdx, ady, bdy, cdy;
  double bdxcdy, cdxbdy, cdxady, adxcdy, adxbdy, bdxady;
  double alift, blift, clift;
  double det;
  double permanent, errbound;

  adx = a.x - d.x;
  bdx = b.x - d.x;
  cdx = c.x - d.x;
  ady = a.y - d.y;
  bdy = b.y - d.y;
  cdy = c.y - d.y;

  bdxcdy = bdx * cdy;
  cdxbdy = cdx * bdy;
  alift = adx * adx + ady * ady;

  cdxady = cdx * ady;
  adxcdy = adx * cdy;
  blift = bdx * bdx + bdy * bdy;

  adxbdy = adx * bdy;
  bdxady = bdx * ady;
  clift = cdx * cdx + cdy * cdy;

  det = alift * (bdxcdy - cdxbdy)
      + blift * (cdxady - adxcdy)
      + clift * (adxbdy - bdxady);

  permanent = (abs(bdxcdy) + abs(cdxbdy)) * alift
            + (abs(cdxady) + abs(adxcdy)) * blift
            + (abs(adxbdy) + abs(bdxady)) * clift;
  double epsilon = numeric_limits<double>::epsilon();
  double iccerrboundA = (10.0 + 96.0 * epsilon) * epsilon;
  errbound = iccerrboundA * permanent;
  if (abs(det) < errbound)
      return Sign::ON;
  if (det > 0)
      return Sign::INSIDE;
  else
      return Sign::OUTSIDE;
}


Sign incircleDouble(const point& a, const point& b, const point& c, const point& d)
{
    double dx = d.x, dy = d.y;
    double ax = a.x, ay = a.y;
    double bx = b.x, by = b.y;
    double cx = c.x, cy = c.y;
    double a00 = ax - dx, a01 = ay - dy;
    double a02 = (ax * ax - dx * dx) + (ay * ay - dy * dy);
    double a10 = bx - dx, a11 = by - dy;
    double a12 = (bx * bx - dx * dx) + (by * by - dy * dy);
    double a20 = cx - dx, a21 = cy - dy;
    double a22 = (cx * cx - dx * dx) + (cy * cy - dy * dy);
    double meps = numeric_limits<double>::epsilon() * 16;
    double d1 = a00 * a11 * a22;
    double d2 = a01 * a12 * a20;
    double d3 = a02 * a10 * a21;
    double d4 = a00 * a12 * a21;
    double d5 = a01 * a10 * a22;
    double d6 = a02 * a11 * a20;
    double det = d1 + d2 + d3 - d4 - d5 - d6;
    double eps = abs(d1) + abs(d2) + abs(d3) + abs(d4) + abs(d5) + abs(d6);
    eps *= meps;
    if (abs(det) < eps)
        return Sign::BOUND;
    else if (det > 0)
        return Sign::INSIDE;
    else
        return Sign::OUTSIDE;
}

Sign incircle(const point& a, const point& b, const point& c, const point& d)
{
    //Sign s = incircleDouble(a, b, c, d);
    Sign s = incircleShewchuckOriginal(a, b, c, d);
    if (s != Sign::BOUND)
        return s;
    mpq_class dx = d.x, dy = d.y;
    mpq_class ax = a.x, ay = a.y;
    mpq_class bx = b.x, by = b.y;
    mpq_class cx = c.x, cy = c.y;
    mpq_class a00 = ax - dx, a01 = ay - dy;
    mpq_class a02 = (ax * ax - dx * dx) + (ay * ay - dy * dy);
    mpq_class a10 = bx - dx, a11 = by - dy;
    mpq_class a12 = (bx * bx - dx * dx) + (by * by - dy * dy);
    mpq_class a20 = cx - dx, a21 = cy - dy;
    mpq_class a22 = (cx * cx - dx * dx) + (cy * cy - dy * dy);
    mpq_class det = a00 * a11 * a22 + a01 * a12 * a20 + a02 * a10 * a21
                  - a00 * a12 * a21 - a01 * a10 * a22 - a02 * a11 * a20;
    if (det == 0)
        return Sign::BOUND;
    else if (det > 0)
        return Sign::INSIDE;
    else
        return Sign::OUTSIDE;
}
