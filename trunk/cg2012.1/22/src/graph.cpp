#include "graph.h"

graph::graph(size_t n) :
    n(n),
    g(n)
{}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p)
{
    return out << "<" << p.first << ", " << p.second << ">";
}

ostream& operator<<(ostream& out, const graph& g)
{
    out << "graph{\n";
    for (size_t i = 0; i < g.n; i++)
    {
        if (g.g[i].size() == 0)
            continue;
        out << i << " -> ";
        for (auto t : g.g[i])
            out << t << " ";
        out << "\n";
    }
    return out << "};";
}

using std::make_pair;

void graph::addEdge(size_t v1, size_t v2, double w)
{
    g[v1].push_back(make_pair(v2,w));
    g[v2].push_back(make_pair(v1,w));
}

#include <queue>
#include <algorithm>

vector<size_t> graph::shortestPath(size_t s, size_t t) const
{
    vector<bool> done(n);
    vector<bool> reached(n);
    vector<size_t> pred(n);
    pred[s] = s;
    reached[s] = true;
    vector<double> d(n);
    std::priority_queue<pair<double, size_t>> q;
    q.push({0, s});
    while (q.size())
    {
        auto now = q.top();
        q.pop();
        double nowW = -now.first;
        size_t nowV = now.second;
        if (done[nowV])
            continue;
        done[nowV] = true;
        for (auto e : g[nowV])
        {
            size_t to = e.first;
            double w = e.second;
            if (!reached[to] || d[to] > nowW + w)
            {
                pred[to] = nowV;
                reached[to] = true;
                d[to] = nowW + w;
                q.push({-d[to], to});
            }
        }
    }
    if (!reached[t])
        return {};
    vector<size_t> result;
    while (s != t)
    {
        result.push_back(t);
        t = pred[t];
    }
    result.push_back(s);
    std::reverse(begin(result), end(result));
    return result;
}
