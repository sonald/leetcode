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

ostream& operator<<(ostream& os, const set<int>& si)
{
    os << "(";
    for (auto v: si) {
        os << v << " ";
    } 
    return os << ")";
}

ostream& operator<<(ostream& os, const unordered_set<int>& si)
{
    os << "(";
    for (auto v: si) {
        os << v << " ";
    } 
    return os << ")";
}


class Solution {
public:
    int countPrimes(int n) {
        int cnt = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime(i)) cnt++;
        }

        return cnt;
    }

    bool isPrime(int d) {
        if (d == 2) return true;

        int r = ceil(sqrt(d));
        for (int i = 2; i <= r; i++) {
            if (d % i == 0) return false;
        }

        return true;
    }
};

class Solution3 {
public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        bool p[n]; // primes
        for (int i = 0; i < n; i++) p[i] = true;

        int c = n/2;
        for (int i = 3; i * i < n; i += 2) {
            if (p[i]) {
                for (int j = i*i; j < n; j += i*2) {
                    if (p[j]) c--;
                    p[j] = false;
                }
            }
        }
        return c;
    }
};

class Solution2 {
public:
    int countPrimes(int n) {
        switch (n) {
            case 0: case 1: case 2: return 0;
            case 3: return 1;
            default: break;
        }

        int total = n/2;
        int v[total+2];
        int p = 2;
        v[0] = 2;
        v[1] = 3;

        for (int i = 5; i < n; i+=2) {
            int k = 0;
            int r = ceil(sqrt(i));
            for (; k < p && v[k] <= r; k++) {
                if (i % v[k] == 0) break;
            }
            if (k == p || v[k] > r) { 
                v[p++] = i;
            }
        }

        return p;
    }
};

int main(int argc, char *argv[])
{
    for (int i = 0; i < 40; i++) {
        cout << i << ": " << Solution().countPrimes(i) << ", "; 
        cout << i << ": " << Solution4().countPrimes(i) << endl; 
    }

    //cout << Solution().countPrimes(1500000) << endl; 
    cout << Solution3().countPrimes(1500000) << endl; 
    //cout << Solution2().countPrimes(1500000) << endl; 
    return 0;
}



