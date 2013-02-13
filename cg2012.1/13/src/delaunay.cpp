#include "delaunay.h"
#include "sign.h"
#include "predicates.h"

#include <cassert>
#include <set>
using std::set;

#include <memory>
using std::shared_ptr;

#include <cmath>
using std::abs;

#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const triangle& t)
{
    return out << t.points[0] << "--" << t.points[1] << "--" << t.points[2];
}

triangle::triangle(const point& p1, const point& p2, const point& p3) 
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Sign intriangle(const point& p, const triangle& t)
{
    Sign s[3];
    for (int i = 0; i < 3; i++)
        s[i] = turn(t.points[i], t.points[(i + 1) % 3], p);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (s[i] == Sign::LEFT && s[j] == Sign::RIGHT)
                return Sign::OUTSIDE;
    for (int i = 0; i < 3; i++)
        if (s[i] == Sign::ON)
            return Sign::BOUND;
    return Sign::INSIDE;
}

struct edge;
typedef edge* pedge;
struct tri;
typedef tri* ptri;

struct edge
{
    point from, to;
    pedge twin;
    ptri t;
};

struct tri
{
    pedge e[3];
    ptri down[3];
    bool alive;
};

triangle to3(const ptri& t)
{
    assert (t->e[0]->to == t->e[1]->from);
    assert (t->e[1]->to == t->e[2]->from);
    assert (t->e[2]->to == t->e[0]->from);
    return {t->e[0]->from, t->e[1]->from, t->e[2]->from};
}

ptri descend(const ptri& t, const point& p)
{
    bool allNulls = true;
    for (ptri tt : t->down)
        allNulls &= tt == nullptr;
    if (allNulls)
        return t;
    for (ptri tt : t->down)
        if (tt != nullptr && intriangle(p, to3(tt)) != Sign::OUTSIDE)
            return descend(tt, p);
    assert (false);
}

bool tryFlip(pedge& e1)
{
    pedge e2 = e1->twin;
    if (e2 == nullptr)
        return false;
    ptri t1 = e1->t;
    ptri t2 = e2->t;
    int free1;
    int free2;
    for (int i = 0; i < 3; i++)
    {
        if (t1->e[i] == e1)
            free1 = (i + 2) % 3;
        if (t2->e[i] == e2)
            free2 = (i + 2) % 3;
    }
    point p1 = t1->e[(free1 + 1) % 3]->from;
    point p2 = t2->e[(free2 + 1) % 3]->from;
    {
        Sign s1 = turn(t1->e[free1]->from, t2->e[free2]->from, p1);
        Sign s2 = turn(t1->e[free1]->from, t2->e[free2]->from, p2);
        if (s1 == s2 && s1 != Sign::ON)
            return false;
    }
    if (incircle(t1->e[0]->from, t1->e[1]->from, t1->e[2]->from, t2->e[free2]->from) == Sign::INSIDE
      ||incircle(t2->e[0]->from, t2->e[1]->from, t2->e[2]->from, t1->e[free1]->from) == Sign::INSIDE)
    {
        pedge newE1 = new edge({t1->e[free1]->from, t2->e[free2]->from, nullptr, nullptr});
        pedge newE2 = new edge({t2->e[free2]->from, t1->e[free1]->from, newE1, nullptr});
        newE1->twin = newE2;
        ptri newT1 = new tri({{t2->e[free2], t1->e[(free1 + 2) % 3], newE1}, {nullptr, nullptr, nullptr}, true});
        ptri newT2 = new tri({{t1->e[free1], t2->e[(free2 + 2) % 3], newE2}, {nullptr, nullptr, nullptr}, true});
        for (int i = 0; i < 3; i++)
        {
            newT1->e[i]->t = newT1;
            newT2->e[i]->t = newT2;
        }
        for (auto t : {t1, t2})
        {
            t->down[0] = newT1;
            t->down[1] = newT2;
            t->alive = false;
        }
        return true;
    }
    return false;
}

void flip(ptri& t)
{
    if (!t->alive)
        return;
    for (pedge e : t->e)
    {
        if (tryFlip(e))
        {
            ptri t1 = e->t->down[0];
            ptri t2 = e->t->down[1];
            flip(t1);
            flip(t2);
            break;
        }
    }
}

void traverse(vector<triangle>& res, ptri t, const triangle& boundTri, set<ptri>& used)
{
    if (used.count(t))
        return;
    used.insert(t);
    if (t->alive)
    {
        bool bound = false;
        for (pedge e : t->e)
            for (point p : boundTri.points)
                bound |= e->from == p;
        if (!bound)
            res.push_back(to3(t));
        for (int i = 0; i < 3; i++)
            assert(!tryFlip(t->e[i]));
    }
    for (ptri tt : t->down)
        if (tt != nullptr)
            traverse(res, tt, boundTri, used);
}

bool between(double a, double b, double c)
{
    return (a <= b && b <= c) || (c <= b && b <= a);
}

bool contains(const point& a, const point& b, const point& c)
{
    if (!between(a.x, b.x, c.x) || !between(a.y, b.y, c.y))
        return false;
    return turn(a, c, b) == Sign::ON;
}

// No three points on same line yet...
void insert(ptri& t, const point& p)
{
    pedge e[2][3];
    pedge te[3];
    for (int i = 0; i < 3; i++)
    {
        e[0][i] = new edge({t->e[i]->from, p, nullptr, nullptr});
        e[1][i] = new edge({p, t->e[i]->from, e[0][i], nullptr});
        e[0][i]->twin = e[1][i];
        te[i] = new edge({t->e[i]->from, t->e[(i + 1) % 3]->from, t->e[i]->twin, nullptr});
        if (te[i]->twin != nullptr)
            te[i]->twin->twin = te[i];
        t->e[i]->twin = nullptr;
    }
    ptri tt[3];
    for (int i = 0; i < 3; i++)
    {
        tt[i] = new tri({{te[i], e[0][(i + 1) % 3], e[1][i]}, {nullptr, nullptr, nullptr}, true});
        t->down[i] = tt[i];
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tt[i]->e[j]->t = tt[i];
    t->alive = false;
    for (int i = 0; i < 3; i++)
        flip(tt[i]);
}

vector<triangle> triangulate(const vector<point>& p)
{
    double mx = 0;
    for (auto pp : p)
    {
        mx = max(mx, abs(pp.x));
        mx = max(mx, abs(pp.y));
    }
    mx *= 8;
    triangle bound({-mx, mx}, {0, -mx}, {mx, mx});
    pedge e1(new edge({bound.points[0], bound.points[1], nullptr, nullptr}));
    pedge e2(new edge({bound.points[1], bound.points[2], nullptr, nullptr}));
    pedge e3(new edge({bound.points[2], bound.points[0], nullptr, nullptr}));
    ptri root(new tri({{e1, e2, e3}, {nullptr, nullptr, nullptr}, true}));
    e1->t = root;
    e2->t = root;
    e3->t = root;
    for (point pp : p)
    {
        assert(intriangle(pp, bound) != Sign::OUTSIDE);
        ptri t = descend(root, pp);
        insert(t, pp);
    }
    vector<triangle> res;
    set<ptri> used;
    traverse(res, root, bound, used);
    return {res};
}
