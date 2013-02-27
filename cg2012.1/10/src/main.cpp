#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

#include "point.h"
#include "mincircle.h"

using namespace std;

bool notin(const point& p, const circle& c);

int main()
{
    size_t n;
    cin >> n;
    vector<point> p(n);
    map<point, int> point2id;
    for (size_t i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
        point2id[p[i]] = i;
    }
    circle c(minimalCoveringCircle(p));
    for (point pp : p)
        assert(!notin(pp, c));
    if (c.n == 2)
        cout << 2 << endl << point2id[c.p[0]] << " " << point2id[c.p[1]] << endl;
    else
        cout << 3 << endl << point2id[c.p[0]] << " "
                          << point2id[c.p[1]] << " "
                          << point2id[c.p[2]] << endl;
}
