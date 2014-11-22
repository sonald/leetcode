#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
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
    vector<int> grayCode(int n) {
        std::vector<int> res {0};
        int k = 0;
        while (k < n) {
            for (int j = res.size()-1; j >= 0; j--)
                res.push_back(res[j] + (1<<k));
            k++;
        }
        return res;
    }
};

void test(int n) {
    cout << Solution().grayCode(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 4; i++) {
        test(i);
    }
    return 0;
}