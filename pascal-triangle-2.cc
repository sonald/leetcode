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
    vector<int> getRow(int numRows) {
        if (numRows < 0) return {};
        numRows++;
        std::vector<int> res(numRows, 0);
        res[0] = 1;
        int last = res[0];

        for (int i = 1; i< numRows; i++) {
            for (int j = 1; j < i; j++) {
                int t = last + res[j];
                last = res[j];
                res[j] = t;
            }
            res[i] = 1;
        }

        return res;
    }
};

class Solution {
public:
    vector<int> getRow(int numRows) {
        if (numRows < 0) return {};
        numRows++;
        std::vector<int> res {1};

        for (int i = 1; i< numRows; i++) {
            std::vector<int> sp {1};
            for (int j = 1; j < res.size(); j++) 
                sp.push_back(res[j-1] + res[j]);
            sp.push_back(1);

            res = std::move(sp);
        }

        return res;
    }
};

void test(int n) {
	cout << Solution2().getRow(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++) test(i);
    return 0;    
}