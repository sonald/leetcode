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

class Solution2 {
public:
    inline std::vector<int> gen(std::vector<int>& S, std::vector<int>& sp) {
        std::vector<int> res;
        for (int i = 0, n = sp.size(); i < n; i++) {
            if (sp[i]) res.push_back(S[i]);
        }
        return std::move(res);
    }

    vector<vector<int> > subsets(vector<int> &S) {
        std::vector<vector<int>> res;
        std::vector<int> sp(S.size(), 0);
        res.push_back(gen(S, sp));

        // .... ditto 
    }
};

// this assumes that S.size() <= sizeof(int), if not, use more generanized 
// version: Solution2
class Solution {
public:
    inline std::vector<int> gen(std::vector<int>& S, unsigned k) {
        std::vector<int> res;
        for (int i = 0, n = S.size(); i < n; i++) {
            if (k & (1<<i)) res.push_back(S[i]);
        }
        return std::move(res);
    }

    vector<vector<int> > subsets(vector<int> &S) {
        std::sort(S.begin(), S.end());
        std::vector<vector<int>> res;
        int total = 1<<S.size(), k = 0;
        while (k < total) {
            res.push_back(gen(S, k));
            k++;
        }

        return res;
    }
};

void test(std::vector<int> v) {
	cout << Solution().subsets(v) << endl;
}

int main(int argc, char const *argv[])
{
    {
        std::vector<int> v {4, 1, 0};
        test(v);
    }
    {
        std::vector<int> v {1, 2, 3};    
        test(v);
    }
    {
        std::vector<int> v {1, 2};    
        test(v);
    }
    {
        std::vector<int> v {1};    
        test(v);
    }

    return 0;    
}