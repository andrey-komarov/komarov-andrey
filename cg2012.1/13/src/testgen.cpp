#include <boost/random.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

using namespace std;

const double PI = M_PI;
const int seed = 477;
const int precision = 30;
boost::random::mt19937 gen(seed);
boost::random::uniform_real_distribution<double> dist(0, 1);

struct point
{
   double x, y;
};

typedef vector<point> test;

template<typename T>
T construct();

template<typename T>
vector<T> range(const T& n)
{
    vector<T> res;
    for (T i = 0; i < n; i++)
        res.push_back(i);
    return res;
}

template<typename T, typename T2>
vector<T> operator+=(vector<T>& a, const T2& b)
{
    for (auto x : b)
        a.push_back(x);
    return a;
}

template<typename T, typename T2>
vector<T> operator+(vector<T> a, const T2& b)
{
    return a += b;
}

template<typename T>
vector<T> operator*(const vector<T> a, size_t n)
{
    vector<T> res;
    for (auto i : range(n))
        for (auto x : a)
            res.push_back(x);
    return res;
}

template<typename A, typename FAB>
auto map(const FAB& f, const vector<A>& a) -> vector<decltype(f(construct<A>()))>
{
    vector<decltype(f(construct<A>()))> res;
    for (auto aa : a)
        res.push_back(f(aa));
    return res;
}

ostream& operator<<(ostream& out, const test& t)
{
    out << t.size() << "\n";
    for (auto p : t)
        out << p.x << " " << p.y << "\n";
    return out;
}

test grid(size_t n, size_t m)
{
    test t;
    for (double i : range(n))
        for (double j : range(m))
            t.push_back({i, j});
    return t;
}

test loggrid(size_t n)
{
    test t;
    double x = 1;
    for (auto i : range(n))
    {
        double y = 1;
        for (auto j : range(n))
        {
            t.push_back({x, y});
            y *= 0.5;
        }
        x *= 0.5;
    }
    return t;
}

test spiral(size_t n, double in2pi, double dl)
{
    double len = 0;
    test res;
    double da = 2 * PI / in2pi;
    for (auto i : range(n))
    {
        res.push_back({len * cos(i * da), len * sin(i * da)});
        len += dl;
    }
    return res;
}

auto shift = [](double dx, double dy){
    return [=](const point& p){
        return point({p.x + dx, p.y + dy});
    };
};

auto blur = [&](double dxL, double dxR) {
    return [&, dxL, dxR](const point& p) {
        return point({p.x + dist(gen) * (dxR - dxL) - dxL
                    , p.y + dist(gen) * (dxR - dxL) - dxL});
    };
};

test fractal2(size_t depth, size_t n, double x, double y, double r, double dr = 3)
{
    double da = 2 * PI / n;
    if (depth == 0)
        return {{x, y}};
    test res;
    for (auto i : range(n))
        res += fractal2(depth - 1, n, x + r * cos(i * da), y + r * sin(i * da), r / dr);
    return res;
}

test random_groups(size_t depth, size_t n, size_t m, double x, double y, double r, double dr = 3)
{
    double da = 2 * PI / n;
    if (depth == 1)
    {
        test res;
        for (auto i : range(m))
        {
            double r2 = dist(gen) * r;
            double a = dist(gen) * 2 * PI;
            double dx = dist(gen) * r;
            double dy = dist(gen) * r;
            res.push_back({x + dx, y + dy});
        }
        return res;
    }
    test res;
    for (auto i : range(n))
    {
        double dx = dist(gen) * r;
        double dy = dist(gen) * r;
        res += random_groups(depth - 1, n, m, x + dx, y + dy, r / dr);
    }
    return res;
}

int main() {
    gen.seed(1);
    vector<test> tests = {
        loggrid(100),
        random_groups(4, 8, 100, 0, 0, 1, 8),
        random_groups(10, 2, 100, 0, 0, 1, 4),
        fractal2(3, 5, 0, 0, 20, 4),
        fractal2(3, 10, 0, 0, 20, 7),
        fractal2(6, 4, 0, 0, 1, 4),
        grid(5, 5),
        grid(10, 2),
        map(shift(1e9, 1e9), grid(50, 50)),
        grid(5, 5) + map(shift(10, 10), grid(5, 5)),
        map(blur(-0.2, 0.2), grid(10, 10)),
        spiral(200, 8.5, 1),
        map(blur(-0.2, 0.2), spiral(200, 8.5, 1)),
        spiral(200, 19.1, 1),
        spiral(200, 3.1, 1),
        spiral(200, 1.2, 1), 
    };
    size_t test = 0;
    for (auto t : tests)
    {
        cerr << test << "\n";
        string testN = boost::lexical_cast<string>(test++);
        testN = string(3 - testN.length(), '0') + testN;
        ofstream out("tests/" + testN);
        out.precision(precision);
        out << t;
    }
    return 0;
}




