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

//inplace solution
class Solution {
public:
    string simplifyPath(string path) {
        if (path.size() == 0) return path;

        auto i = path.begin()+1;
        while (i != path.end()) {
            if (*i == '/' && *(i-1) == *i)
                i = path.erase(i);
            else i++;
        }
        i--; 
        if (*i == '/' && path.size() > 1) path.erase(i);
        if (path.size() == 1) return path;

        auto p = path.begin(), q = p;
        while (p != path.end()) {
            // cout << "path: " << path << endl;
            q = find(p+1, path.end(), '/');
            string sub = path.substr(p-path.begin(), q-p);
            if (sub == "/.") {
                if (p == path.begin() && q == path.end()) return "/";
                p = path.erase(p, q);
            } else if (sub == "/..") {
                if (p == path.begin()) {
                    if (q == path.end()) p = path.erase(p+1, q);
                    else p = path.erase(p, q);
                } else {
                    q = p = path.erase(p, q);
                    while (*--p != '/');
                    p = path.erase(p, q);
                    if (path.size() == 0) return "/";
                }
            } else p = q;
            p = find(p, path.end(), '/');                    
        }

        return path;
    }
};

void test(string s) {
	cout << Solution().simplifyPath(s) << endl;
}

int main(int argc, char const *argv[])
{
    test("///");
    test("///home//s/..//b//"); // /home/b
    test("/home//");   // /home
    test("/a/./b///../c/../././../d/..//../e/./f/./g/././//.//h///././/..///"); // '/e/f/g'
    test("///eHx/.."); // '/'
    test("//./cc//"); // '/cc'
    test("//."); // '/'
    test("/a/./b/../../c/"); // '/c'
    test("/../"); // '/'
    test("/../a"); // '/a'
    test("/../../root"); // '/root'    
    test("/a///./../b"); // '/b'
    return 0;    
}