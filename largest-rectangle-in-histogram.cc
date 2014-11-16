#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

ostream& operator<<(ostream& os, const pair<int, int>& p)
{
    return os << "(" << p.first << "," << p.second << ")";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]";
}

// basically the same idea as Solution, but more elegant
class Solution2 {
public:
    int largestRectangleArea(vector<int> &height) {
        std::vector<pair<int, int>> sp; // <high, index>
        int res = 0;
        height.push_back(0);
        sp.emplace_back(0, -1); // sentinal
        int i = 0;
        while (i < height.size()) {
            int k = height[i];
            if (sp.size() && sp.back().first <= k) {
                sp.emplace_back(k, i++);
            } else {
                auto p = sp.back();
                sp.pop_back();                
                res = max((i-sp.back().second-1) * p.first,  res);
            }
        }

        while (sp.size() > 1) {
            auto p = sp.back();
            sp.pop_back();                
            res = max((i-sp.back().second-1) * p.first,  res);            
        }
        return res;        
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        std::vector<pair<int, int>> sp; // <high, index>
        int res = 0;
        sp.emplace_back(0, -1);
        for (int i = 0, n = height.size(); i < n; i++) {
            int k = height[i];
            bool dropping = false;
            while (sp.size() && sp.back().first >= k) {
                sp.pop_back();
                dropping = true;
            }
            sp.emplace_back(k, i);

            if (dropping || i == n-1 || (sp.back().first >= height[i+1])) {
                // cout << "i = " << i << ", sp: " << sp << endl;
                for (int p = 1; p < sp.size(); p++) {
                    auto r = sp[p].first * (i - sp[p-1].second);
                    res = max(r, res);
                }
            }            
        }

        return res;        
    }
};

void test(vector<int> &height) {
    cout << Solution2().largestRectangleArea(height) << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<int> v;        
        for (int i = 0; i < 9000; i++)
            v.push_back(i);
        test(v); // 20250000
    }
    {
        std::vector<int> v {0};
        test(v); // 0
    }
    {
        std::vector<int> v {3,2,5,0,6,2,3};
        test(v); // 6
    }
    {
        std::vector<int> v {3,2,5,6,2,3};
        test(v); // 12
    }
    {
        std::vector<int> v {2,1,5,0,2,3};
        test(v); // 5
    }
    {
        std::vector<int> v {2,1,5,6,2,3};
        test(v); // 10
    }
    return 0;
}