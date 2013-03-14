#include "vizibility.h"

#include <algorithm>
using std::min;
using std::max;

#include "predicates.h"
#include <cassert>
#include <set>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const segment& s)
{
    return out << "[" << s.a << "--" << s.b << "]";
}

template<typename T, typename T2>
std::ostream& operator<<(std::ostream& out, const std::set<T, T2>& v)
{
    out << "[";
    for (auto x : v)
        out << x << " ";
    return out << "]";
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& v)
{
    out << "[";
    for (size_t i = 0; i <v.size(); i++)
    {
        out << v[i];
        if (i != v.size() - 1)
            out << ", ";
    }
    return out << "]";
}

segment::segment(const point& a, const point& b) :
    a(min(a, b)),
    b(max(a, b))
{}

bool segment::operator==(const segment& s) const
{
    return a == s.a && b == s.b;
}

template<typename C, typename T>
std::function<void(const T&)> inserter(C& c);

template<typename T>
std::function<void(const T&)> inserter(vector<T>& v)
{
    return [&v](const T& a) {
        return v.push_back(a);
    };
}

struct event
{
    point p;
    size_t segId;
    bool open;
};

std::ostream& operator<<(std::ostream& out, const event& e)
{
    return out << "{" << e.p << ", " << e.segId << ", " << e.open << "}";
}

template<typename T>
bool between(const T& a, const T& b, const T& c)
{
    return (a <= b && b <= c) || (c <= b && b <= a);
}

struct byangle
{
    point o;
    point ox;
    byangle(const point& p) :
        o(p),
        ox(p.x + abs(p.x) + 1, p.y)
    {}

    bool operator()(const event& e1, const event& e2) const
    {
        if (e1.p == e2.p)
            return e1.open < e2.open; // TODO: оторвать руки за op<(bool, bool)
        if (e1.p == o)
            return !(e2.p == o); // TODO: оторвать руки за лень реализовать op!=
        if (e2.p == o)
            return false;
        Sign s1 = turn(o, ox, e1.p);
        Sign s2 = turn(o, ox, e2.p);
        if (s1 == Sign::LEFT && s2 == Sign::RIGHT)
            return true;
        if (s1 == Sign::RIGHT && s2 == Sign::LEFT)
            return false;
        if (s1 == Sign::ON && s2 == Sign::ON)
        {
            if (between(o.x, e1.p.x, e2.p.x))
                return true;
            if (between(o.x, e2.p.x, e1.p.x))
                return false;
            return e1.p.x > e2.p.x;
        }
        Sign s = turn(o, e1.p, e2.p);
        if (s != Sign::ON)
            return s == Sign::RIGHT;
        return between(o.x, e1.p.x, e2.p.x) && between(o.y, e1.p.y, e2.p.y);
    }
};

struct around
{
    point o;
    around(const point& p) :
        o(p)
    {}

    bool operator()(const segment& s1, const segment& s2) const
    {
        if (s1 == s2)
            return false;
        Sign ss[2][2] = {
            { turn(s1.a, s1.b, s2.a), turn(s1.a, s1.b, s2.b) },
            { turn(s2.a, s2.b, s1.a), turn(s2.a, s2.b, s1.b) }
        };
        assert (ss[0][0] != Sign::ON || ss[0][1] != Sign::ON 
          ||ss[1][0] != Sign::ON || ss[1][1] != Sign::ON);
        if (ss[0][0] != Sign::LEFT && ss[0][1] != Sign::LEFT)
            return true;
        if (ss[1][0] != Sign::RIGHT && ss[1][1] != Sign::RIGHT)
            return true;
        return false;
    }
};

bool rayIntersects(const point& o, const point& p, const segment& s)
{
    Sign s1 = turn(o, p, s.a);
    Sign s2 = turn(o, p, s.b);
    if (s1 == Sign::ON)
        return true;
    if (s2 == Sign::ON)
        return false;
    if (s1 != s2)
        return true;
    return false;
}

vector<point> visible(vector<segment> ss, const point& p)
{
    for (segment& s : ss)
        if (turn(p, s.a, s.b) == Sign::LEFT)
            std::swap(s.a, s.b);
    vector<point> ans;
    auto ins = inserter(ans);
    point r({2 * p.x + 1, p.y});
    vector<event> events;
    auto eins = inserter(events);
    for (size_t i = 0; i < ss.size(); i++) 
    {
        segment s = ss[i];
        eins({s.b, i, true});
        eins({s.a, i, false});
    }
    sort(begin(events), end(events), byangle(p));
    around cmpt(p);
    std::set<segment, around> status(cmpt);
    vector<bool> used(ss.size());
    for (auto e : events)
    {
        if (e.open)
        {
            status.insert(ss[e.segId]);
            used[e.segId] = true;
        }
        else
        {
            status.erase(ss[e.segId]);
            used[e.segId] = false;
        }
    }

    for (auto e : events)
    {
        if (e.open)
        {
            status.insert(ss[e.segId]);
        }
        if (status.size() > 0)
        {
            auto nearest = *status.rbegin();
            if (e.p == nearest.a || e.p == nearest.b)
                ins(e.p);
        }
        if (!e.open)
        {
            status.erase(ss[e.segId]);
        }
    }
    std::set<point> preRes(ans.begin(), ans.end());
    return vector<point>(preRes.begin(), preRes.end());
}
