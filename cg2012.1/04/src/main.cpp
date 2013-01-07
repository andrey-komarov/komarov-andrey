#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <utility>

#include "segment.h"
#include "orientation.h"

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::cerr;

typedef vector<point> poly;

using std::ostream;
template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
    out << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != v.size() - 1)
            out << v[i] << ", ";
        else
            out << v[i];
    }
    out << "]";
    return out;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p)
{
    return out << "{" << p.first << ", " << p.second << "}";
}

poly read()
{
    size_t n;
    cin >> n;
    poly p(n);
    for (size_t i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    return p;
}

pair<bool, Sign> rayRightIntersects(const segment& s, const point& p)
{
    if (p == s.a || p == s.b)
        return make_pair(true, EQUAL);
    if (p.y == s.a.y && s.b.y == p.y)
    {
        if (s.a.x <= p.x && p.x <= s.b.y)
            return make_pair(true, EQUAL);
        else
            return make_pair(false, EQUAL);
    }
    if (p.y <= s.a.y || s.b.y < p.y)
        return make_pair(false, EQUAL);
    Sign sg = orientation(s, p);
    return make_pair(sg != RIGHT, sg);
}

int main()
{
    vector<poly> p;
    p.push_back(read());
    size_t n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
        p.push_back(read());
    vector<segment> s;
    for (poly q : p)
    {
        size_t n = q.size();
        for (size_t i = 0; i < n; i++)
        {
            point here = q[i];
            point next = q[(i + 1) % n];
            if (here.y < next.y || (here.y == next.y && here.x < next.x))
                s.push_back(segment(here, next));
            else
                s.push_back(segment(next, here));
        }
    }
    size_t k;
    cin >> k;
    vector<int> answers;
    for (size_t q = 0; q < k; q++)
    {
        point p;
        cin >> p.x >> p.y;
//        cerr << "Processing " << p << "\n";
        size_t intersectsNum = 0;
        bool onBound = false;
        for (segment sg : s)
        {
            auto res = rayRightIntersects(sg, p);
            if (res.first)
            {
                if (res.second == EQUAL)
                {
                    onBound = true;
                    break;
                }
                if (res.second == LEFT)
                    intersectsNum++;
            }
//            cerr << sg << " : " << res << "\n";
        }
        if (onBound)
            answers.push_back(0);
        else if (intersectsNum % 2 == 0)
            answers.push_back(-1);
        else
            answers.push_back(1);
    }
    for (int s : answers)
        cout << s << "\n";
}
