#ifndef graph_h
#define graph_h

#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <cstddef>
#include <ostream>
using std::ostream;

struct graph
{
    size_t n;
    vector<vector<pair<size_t, double>>> g;
public:
    graph(size_t n);
    void addEdge(size_t v1, size_t v2, double w);
    vector<size_t> shortestPath(size_t v1, size_t v2) const;
};

template<typename T1, typename T2>
ostream& operator<<(ostream&, const pair<T1, T2>&);
ostream& operator<<(ostream&, const graph&);

#endif
