#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <limits>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (auto i: v) {
        os << i << " ";
    }
    
    return os << "]";
}

// bruteforce solution
class Solution2 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        for (const auto& e: edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        return bruteforce();
    }

    int mind = 0;
    vector<int> bruteforce() {
        vector<int> res;
        mind = std::numeric_limits<int>::max();

        for (int i = 0, n = adj.size(); i < n; ++i) {
            int d = 0;
            visited.clear();
            visited[i] = true;
            dfs(d, 0, i);
            if (d < mind) {
                mind = d;
                res.clear();
                res.push_back(i);
            } else if (d == mind) {
                res.push_back(i);
            }
        }
        return res;
    }

    void dfs(int& d, int l, int u) {
        if (d < l) d = l;
        if (d > mind) return;

        for (auto& v: adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(d, l+1, v);
                if (d > mind) return;
            }
        }
    }

private:
    vector<vector<int>> adj;
    unordered_map<int, bool> visited;
};

//the trick is that the graph can only have at most 2 MHTs
class Solution2 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        for (int i = 0; i < n; i++) adj[i] = {};
        for (const auto& e: edges) {
            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }

        return bruteforce();
    }

    vector<int> bruteforce() {
        vector<int> res;

        while (adj.size() > 2) {
            vector<int> sp;
            for (const auto& p: adj) {
                if (p.second.size() == 1) {
                    sp.push_back(p.first);
                }
            }

            for (auto v: sp) {
                adj[*adj[v].begin()].erase(v);
                adj.erase(v);
            }
        }

        for (auto v: adj) {
            res.push_back(v.first);
        }
        return res;
    }

private:
    unordered_map<int, unordered_set<int>> adj;
};

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        for (int i = 0; i < n; i++) adj[i] = {};
        for (const auto& e: edges) {
            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }

        return bruteforce();
    }

    vector<int> bruteforce() {
        vector<int> res;

        while (adj.size() > 2) {
            vector<int> sp;
            for (const auto& p: adj) {
                if (p.second.size() == 1) {
                    sp.push_back(p.first);
                }
            }

            for (auto v: sp) {
                adj[*adj[v].begin()].erase(v);
                adj.erase(v);
            }
        }

        for (auto v: adj) {
            res.push_back(v.first);
        }
        return res;
    }

private:
    vector<pair<int, unordered_set<int>>> adj;
};


int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> edges = {};
        cout << Solution().findMinHeightTrees(1, edges) << endl; // [0]
    }
    {
        vector<vector<int>> edges = {{0, 1}};
        cout << Solution().findMinHeightTrees(2, edges) << endl; // [0, 1]
    }
    {
        vector<vector<int>> edges = {{1, 0}, {1, 2}, {1, 3}};
        cout << Solution().findMinHeightTrees(4, edges) << endl; // 1
    }
    {
        vector<vector<int>> edges = {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}};
        cout << Solution().findMinHeightTrees(6, edges) << endl; // 3,4
    }
    
    {
        vector<vector<int>> edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
        cout << Solution().findMinHeightTrees(6, edges) << endl; // 3
    }
    return 0;    
}
