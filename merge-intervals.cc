
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

// DO not use vector erase in OJ
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        std::sort(intervals.begin(), intervals.end(), [=](const Interval& i1, const Interval& i2) {
            return i1.start < i2.start;
            // return std::less<int>()(i1.start, i2.start);
        });

        if (intervals.size() <= 1) return intervals;
        std::vector<Interval>::iterator prev = intervals.begin();

        auto i = prev + 1;
        while (i != intervals.end()) {
            if (prev->end >= i->start) {
                prev->end = max(prev->end, i->end);
                intervals.erase(i); // this is really slow
                i = prev + 1;
            } else {
                prev = i++;
            }
        }

        return intervals;
    }
};

class Solution2 {
public:
    static bool compare(const Interval& i1, const Interval& i2) {
        return std::less<int>()(i1.start, i2.start);
    }

    vector<Interval> merge(vector<Interval> &intervals) {
        //?FIXME: OJ don't support it
        // std::sort(intervals.begin(), intervals.end(), [=](const Interval& i1, const Interval& i2) {
        //     // return i1.start < i2.start;
        //     return std::less<int>()(i1.start, i2.start);
        // });

        std::sort(intervals.begin(), intervals.end(), Solution2::compare);
        if (intervals.size() <= 0) return intervals;
        std::vector<Interval> res;
        int n = intervals.size();
        res.push_back(intervals[0]);
        int i = 1;
        while (i < n) {
            auto& p = res.back();
            if (p.end >= intervals[i].start) {
                p.end = max(p.end, intervals[i].end);
            } else {
                res.push_back(intervals[i]);
            }
            ++i;            
        }

        return res;
    }
};

void test(vector<Interval> intervals) {
    cout << Solution2().merge(intervals) << endl;
}

int main(int argc, char const *argv[])
{
    test({});
    test({{3, 4}});
    test({{1, 4}, {5, 6}});
    test({{1, 3}, {8, 10}, {2, 6}, {15, 18}});

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);
    std::vector<Interval> v;
    for (int k = 0; k < 20000; k++) {
        Interval i;
        i.start = dis(gen);
        i.end = i.start + dis(gen);
        v.push_back(i);
    }
    test(v);

    return 0;
}