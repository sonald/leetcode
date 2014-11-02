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

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

//http://decomplexify.blogspot.com/2014/05/permutations.html
class Solution2 {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        vector<vector<int>> result;
        result.push_back(num);
        while (true){
            if (!nextLargePermutation(num)) break;

            result.push_back(num);
        }
        return result;
    }

    bool nextLargePermutation(vector<int> &num){
        int i=num.size()-2;
        for (; i>=0 && num[i] >= num[i+1]; i--) {}

        if (i<0) return false;

        int j=num.size()-1;
        for (; j>i && num[j] <= num[i]; j--) {}

        swap(num[i], num[j]);
        sort(num.begin()+i+1, num.end());
        return true;
    }
};

class Solution {
public:
	vector<vector<int> > permuteUnique(vector<int> &num) {
		if (num.size() == 1) {
			return {{num[0]}};
		}

		vector<vector<int>> res;
		set<int> done;

		for (int i = 0, n = num.size(); i < n; ++i) {
			auto rx = num.begin() + i;
			int x = *rx;
			if (done.find(x) != done.end()) continue;
			done.insert(x);
			num.erase(rx);
			// cout << "pick " << x << endl;
			auto vvi = permuteUnique(num);
			for (auto& vi: vvi) {
				vi.insert(vi.begin(), x);
				res.push_back(vi);
			}
			num.insert(rx, x);
		}
		return res;
	}
};


void test(std::vector<int> v) {
	cout << Solution().permuteUnique(v) << endl;
}

int main(int argc, char const *argv[])
{
	test({1,1,2});
	return 0;
}