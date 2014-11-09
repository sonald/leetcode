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
    vector<vector<int> > combine(int n, int k) {
     	std::vector<vector<int>> res;

	}
};

class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
     	std::vector<vector<int>> res;

     	std::set<int> sp;
     	for (int i = 1; i <= n; i++) sp.insert(i);

     	return gen(sp, n, 1, k);
    }

    vector<vector<int> > gen(set<int>& sp, int n, int t, int k) {
     	if (sp.size() == k) {
     		std::vector<int> v;
     		for (auto& x: sp) v.push_back(x);
     		return {v};
     	}

     	std::vector<vector<int>> res;
     	for (int i = t; i <= n; i++) {
     		sp.erase(i);
     		auto&& tmp = gen(sp, n, i+1, k);
     		std::move(tmp.begin(), tmp.end(), back_inserter(res));
     		sp.insert(i);
     	}
     	return res;
    }

};

void test(int n, int k) {
	cout << Solution().combine(n, k) << endl;
}

int main(int argc, char const *argv[])
{
	for (int n = 5, i = 0; i <= n; i++) 
		test(n, i);
	test(1, 1);
	test(2, 1);
	test(4, 2);
	return 0;
}