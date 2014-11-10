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

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]";
}

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        if (numRows <= 0) return {};
        vector<vector<int>> res;

        res.push_back({1});
        for (int i = 1; i< numRows; i++) {
            auto& last = res[i-1];
            std::vector<int> sp {1};
            for (int j = 1; j < last.size(); j++) 
                sp.push_back(last[j-1] + last[j]);
            sp.push_back(1);
            res.push_back(sp);
        }

        return res;
    }
};

void test(int n) {
	cout << Solution().generate(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++) test(i);
    return 0;    
}