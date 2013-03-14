#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <set>

#include "point.h"
#include "vizibility.h"
#include "graph.h"

using namespace std;

template<typename K, typename V>
ostream& operator<<(ostream& out, const map<K, V> m)
{
    out << "{";
    for (auto p : m)
    {
        out << "[" << p.first << " -> " << p.second << "]";
    }
    return out << "}";
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
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

template<template<typename> class C, typename T>
ostream& operator<<(ostream& out, const C<T>& c)
{
    out << "[";
    for (auto t : c)
        out << t << " ";
    return out << "]";
}

int main()
{
    point s, t;
    cin >> s.x >> s.y >> t.x >> t.y;
    size_t n;
    cin >> n;
    vector<segment> ss;
    map<point, size_t> p2id;
    size_t points = 2;
    p2id[s] = 0;
    p2id[t] = 1;
    vector<vector<point>> polygons;
    for (size_t i = 0; i < n; i++)
    {
        size_t k;
        cin >> k;
        vector<point> p(k);
        for (size_t j = 0; j < k; j++)
            cin >> p[j].x >> p[j].y;
        polygons.push_back(p);
        for (size_t j = 0; j < k; j++)
            ss.push_back({p[j], p[(j + 1) % k]});
        for (auto pp : p)
            if (!p2id.count(pp))
                p2id[pp] = points++;
    }
    map<size_t, point> id2p;
    for (auto p_id : p2id)
        id2p[p_id.second] = p_id.first;
    graph g(points);
    auto sqr= [](double x){return x * x;};
    auto dist = [sqr](const point& p1, const point& p2) {
        return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
    };

    map<point, set<point>> vis;
    for (auto p_id : p2id)
    {
        auto fromP = p_id.first;
        auto visP = visible(ss, fromP);
        vis[fromP] = set<point>(visP.begin(), visP.end());
//        cerr << "Visible from " << fromP << " is " << visP << "\n";
    }

    for (vector<point> poly : polygons)
        for (size_t i = 0; i < poly.size(); i++)
            for (size_t j = 0; j < poly.size(); j++)
                vis[poly[i]].erase(poly[j]);
    for (vector<point> poly : polygons)
        for (size_t i = 0; i < poly.size(); i++)
        {
            size_t next = (i + 1) % poly.size();
            size_t prev = (i + poly.size() - 1) % poly.size();
            vis[poly[i]].insert(poly[next]);
            vis[poly[i]].insert(poly[prev]);
        }

    for (pair<point, set<point>> p : vis)
    {
        point from = p.first;
        for (point to : p.second)
            g.addEdge(p2id[from], p2id[to], dist(from, to));
    }

//    cerr << g << "\n";
//    cerr << id2p << "\n";
//    cerr << p2id << "\n";
    auto path = g.shortestPath(p2id[s], p2id[t]);
    cout << path.size() << "\n";
    for (size_t p : path)
        cout << id2p[p].x << " " << id2p[p].y << "\n";
}
