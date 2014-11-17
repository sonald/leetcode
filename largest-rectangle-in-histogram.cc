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
#include <cmath>

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

class SegmentTree {
public:
    std::vector<int> nodes;
    int n;

    SegmentTree(const vector<int>& v) {
        n = v.size();
        int h = std::ceil(std::log2(n)); 
        nodes = std::vector<int>(2*std::pow(2,h)-1, 0);

        build(v, 0, 0, n-1);        
    }

    int query(const vector<int>& v, int ql, int qr) const {
        return queryMin(v, 0, 0, n-1, ql, qr);
    }

private:
    int idOfMin(const vector<int>& v, int id1, int id2) const {
        if (id1 == INT_MAX) return id2;
        else if (id2 == INT_MAX) return id1;

        return (v[id1] < v[id2]) ? id1 : id2;
    }

    // [l, r] is region of id, [ql, qr] is query region
    int queryMin(const vector<int>& v, int id, int l, int r, int ql, int qr) const {
        if (ql <= l && qr >= r) return nodes[id];
        if (ql > r || qr < l) return INT_MAX;

        int mid = l + (r - l) / 2;
        return idOfMin(v, queryMin(v, id*2+1, l, mid, ql, qr), queryMin(v, id*2+2, mid+1, r, ql, qr));
    }

    int build(const vector<int>& v, int id, int l, int r) {
        if (l == r) {
            return nodes[id] = l;
        }

        int mid = l + (r-l)/2;
        return nodes[id] = idOfMin(v, build(v, id*2+1, l, mid), build(v, id*2+2, mid+1, r));
    }

};

class Solution3 {
public:
    int largestRectangleArea(vector<int> &height) {
        if (height.size() == 0) return 0;
        SegmentTree st(height);
        return dac(height, st, 0, height.size()-1);
    }

    int dac(const vector<int>& height, const SegmentTree& st, int l, int r) {
        if (l > r) return -1;
        if (l == r) return height[l];
        int id = st.query(height, l, r);
        return max(max(dac(height, st, l, id-1), dac(height, st, id+1, r)), (r-l+1)*height[id]);
    }
};

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
    cout << Solution3().largestRectangleArea(height) << " ";        
    cout << Solution().largestRectangleArea(height) << " ";
    cout << Solution2().largestRectangleArea(height) << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    {
        std::vector<int> v {3,2,5,0,6,2,3};        
        std::vector<int> v2 {2,1,5,6,2,3};

        SegmentTree st(v);
        cout << st.nodes << endl;
        cout << "query " << st.query(v, 0, v.size()-1) << endl;
        cout << "query " << st.query(v, 2, 6) << endl;        

        SegmentTree st2(v2);        
        cout << st2.nodes << endl;
        cout << "query " << st2.query(v2, 0, v2.size()-1) << endl;
        cout << "query " << st2.query(v2, 2, 5) << endl;
        // return 0;
    }

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