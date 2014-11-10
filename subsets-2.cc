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
    vector<vector<int>> gen(std::vector<int>& S, int k) {
        vector<vector<int>> res;
        if (S.size() == 0) return {{}};
        res.push_back(S);

        for (int i = k, n = S.size(); i < n; i++) {
            if (i > 0 && S[i] == S[i-1]) continue;
            auto t = S[i];
            S.erase(S.begin()+i);

            auto&& tmp = gen(S, i);
            for (auto&& x: tmp) res.push_back(x);
            S.insert(S.begin()+i, t);
        }

        return res;
    }

    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        std::sort(S.begin(), S.end());
        return gen(S, 0);
    }
};

void test(std::vector<int> v) {
	cout << Solution().subsetsWithDup(v) << endl;
}

int main(int argc, char const *argv[])
{
    {
        std::vector<int> v {1, 2, 3, 3};
        test(v);
    }
    {
        std::vector<int> v {1, 2, 2};    
        test(v);
    }
    {
        std::vector<int> v {1, 2, 2, 2};    
        test(v);
    }

    return 0;    
}