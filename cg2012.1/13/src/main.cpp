#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "point.h"
#include "delaunay.h"

using namespace std;

int main()
{
    size_t n;
    cin >> n;
    vector<point> a;
    map<point, int> point2id;
    for (size_t i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        point p(x, y);
        a.push_back(p);
        point2id[p] = i + 1;
    }
    random_shuffle(a.begin(), a.end());
    auto b = triangulate(a);

//    for (auto t : b)
//        cout << t << "\n";
//    return 0 ;

    cout << b.size() << "\n";
    for (auto t : b)
    {
        for (point p : t.points)
            cout << point2id[p] << " ";
        cout << "\n";
    }
}
