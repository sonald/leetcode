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

ostream& operator<<(ostream& os, const vector<string>& vs)
{
    for (auto& s: vs) {
        os << s << ",";
    }
    return os;
}

class Solution {
public:
	unordered_map<char, int> ord; // count of chars in t
	unordered_map<char, int> sp;  // current result counting
	void shrink(string& S, int& l) {
		auto c = S[l];
		while (1) {
			if (sp[c] > ord[c]) {
				sp[c]--; l++;
				while (ord.find(S[l]) == ord.end()) l++;
				c = S[l];
			} else break;
		}
	}

	string minWindow(string S, string T) {
    	for (auto& ch: T) { ord[ch]++; }

    	pair<int, int> range, rg;
    	int n = S.size(), l = 0, r = 0;
		while (l < n && ord.find(S[l]) == ord.end()) { l++; r++; }

		//find first result
		auto m = ord;
		while (r < n && m.size()) {
			auto k = m.find(S[r]);
			if (k != m.end()) {
				if (--(k->second) == 0) m.erase(k);
			}
			if (ord.find(S[r]) != ord.end())
				sp[S[r]]++;	

			r++;
		}		
		if (m.size()) return "";
		shrink(S, l);
		range = {l, r-l};

		rg = range;
		sp[S[rg.first]]--;
		l++;
    	while (l < n && r < n) {
    		if (ord.find(S[l]) == ord.end()) {
    			l++; continue;
    		}

    		while (r < n && S[r] != S[rg.first]) {
    			if (ord.find(S[r]) != ord.end()) sp[S[r]]++;
    			r++;
    		}    		
    		if (r == n) break;
    		sp[S[r]]++;
 			shrink(S, l);
    		rg = {l, r-l+1};
    		if (range.second > rg.second) range = rg;
    		l++; r++;
    		sp[S[rg.first]]--;
    	}

    	return S.substr(range.first, range.second);
    }
};

void test(string s, string t)
{
    cout << Solution().minWindow(s, t) << endl;
}

int main(int argc, char *argv[])
{
    test("ADOBECODEBANC", "ABC");  // BANC
    test("ADBOBECODEBANC", "ABC");  // BANC
    test("ADBOBECODEBANC", "AABC");  //ADBOBECODEBA
    test("ADBOBECODEBANC", "ABBC");  //ADBOBEC
    test("bba", "ab"); // ba
    return 0;
}

