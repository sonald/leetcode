#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T, class U>
ostream& operator<<(ostream& os, const unordered_map<T, U>& v)
{
    os << "{";
    for (const auto& t: v) {
        os << "(" << t.first << ":" << t.second << ")";
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

/**
 * Definition for a point.
**/
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(";
    os << p.x << "," << p.y;
    return os << ")";
}

class Solution2 {
    public:
        int maxPoints(vector<Point> &points) {
            return 0;
        }
};

//O(n*n)
class Solution {
    public:
        double slope(const Point& p1, const Point& p2) {
            if (p1.y == p2.y) return std::numeric_limits<double>::infinity();
            return ((double)(p1.x - p2.x) / (p1.y - p2.y));
        }

        int maxPoints(vector<Point> &points) {
            int n = points.size();
            if (n <= 2) return n;

            int res = std::numeric_limits<int>::min();
            for (int i = 0; i < n; i++) {
                int rep = 1;
                unordered_map<double, int> m;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        if (points[i].x == points[j].x && points[i].y == points[j].y)
                            rep++;
                        else 
                            m[slope(points[i], points[j])]++;
                    }
                }

                if (m.size()) {
                    for (auto& x: m) {
                        res = max(res, x.second + rep);
                    }
                } else {
                    res = max(res, rep);
                }
            }

            return res;
        }
};

void test(vector<Point> points) {
    cout << Solution().maxPoints(points) << endl;
}

int main(int argc, char const *argv[])
{
    test({{1,1}, {3,3}, {5, 5}, {1, 2}, {5, 7}, {4, 1}, {5, 1}, {10, 1}, {12, 1}}); //5
    test({{0,0},{1,1},{1,-1}}); // 2
    test({{2,3},{3,3},{-5,3}}); // 3
    test({{0,0},{-1,-1},{2,2}}); //3
    test({{1,1},{1,1},{2,2},{2,2}}); // 4
    return 0;
}
