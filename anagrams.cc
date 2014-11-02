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

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
    	unordered_map<std::size_t, vector<string>> groups;
    	for (auto& s: strs) {
    		string ss(s);
    		sort(ss.begin(), ss.end());
    		groups[std::hash<string>()(ss)].push_back(s);
    	}    

    	std::vector<string> res;
    	for (auto& x: groups) {
    		if (x.second.size() > 1) {
    			res.insert(res.end(), x.second.begin(), x.second.end());
    		}
    	}

    	return res;
    }
};

void test(std::vector<string> v) {
	cout << Solution().anagrams(v) << endl;
}

int main(int argc, char const *argv[])
{
	test({""});
	test({"good", "bad", "dogo"});
	return 0;
}