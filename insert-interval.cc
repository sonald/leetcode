
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

/**
 * Definition for an interval.
 */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

ostream& operator<<(ostream& os, const Interval& i)
{
    return os << "<" << i.start << "," << i.end << ">";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "{ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "}\n";
}

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        if (intervals.size() <= 0) return {newInterval};
        std::vector<Interval> res;
        int n = intervals.size();

        bool inserted = false;
        int i = 0;
        while (i < n) {
            if (inserted) {
                res.push_back(intervals[i++]);
                continue;
            }

            if (intervals[i].end < newInterval.start) {
                res.push_back(intervals[i]); ++i;
                continue;
            }

            res.push_back(newInterval);                           
            if (newInterval.end < intervals[i].start) {
                inserted = true; continue;
            }
            auto& p = res.back();
            p.start = std::min(p.start, intervals[i].start);
            while (i < n && intervals[i].end < newInterval.end) {
                ++i;
            }

            if (i == n) 
                p.end = max(intervals[n-1].end, p.end);
            else if (newInterval.end < intervals[i].start)
                p.end = newInterval.end;
            else {
                p.end = intervals[i].end;
                ++i;  
            }
            inserted = true;
        }

        if (!inserted) res.push_back(newInterval);
        return res;
        
    }
};

void test(vector<Interval> intervals, Interval in) {
    cout << Solution().insert(intervals, in) << endl;
}

int main(int argc, char const *argv[])
{
    test({}, {1, 3});
    test({{1, 5}}, {2, 7});
    test({{1, 5}}, {6, 7});
    test({{1, 5}}, {2, 3});
    test({{3, 4}}, {1, 2});
    test({{3, 5}}, {1, 4});    
    test({{3, 5}}, {1, 8});        
    test({{1, 4}, {5, 6}}, {2, 6});
    test({{1, 2}, {5, 6}}, {2, 4});
    test({{1, 2}, {8, 9}}, {3, 4});
    test({{1, 2}, {3, 6}, {8, 10}, {15, 18}}, {2, 16});
    test({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 9});


    return 0;
}