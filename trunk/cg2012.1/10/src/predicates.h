#ifndef PREDICATES_H
#define PREDICATES_H
#include "sign.h"
#include "point.h"

Sign turn(const point& a, const point& b, const point& c);
Sign incircle(const point& a, const point& b, const point& c, const point& d);
Sign incircle(const point& a, const point& b, const point& c);

#endif
