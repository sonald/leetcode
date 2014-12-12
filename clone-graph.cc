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

template <class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
    os << "{";
    for (const auto& p: v) {
        os << "(" << p.first << ": " << p.second << ")";
    }
    return os << "}\n";
}

template <class T, class S>
ostream& operator<<(ostream& os, const pair<T, S>& p)
{
    return os << p.first << "," << p.second;
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

/**
 * Definition for undirected graph.
*/
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

void dump(UndirectedGraphNode* nd)
{
    unordered_map<UndirectedGraphNode*, bool> used;
    vector<UndirectedGraphNode*> sp {nd};
    while (sp.size()) {
        auto* n = sp.back(); sp.pop_back();
        used[n] = true;
        cout << n->label;
        for (auto& x: n->neighbors) {
            cout << "," << x->label;
            if (!used[x]) sp.push_back(x);
        }
        cout << "#";
    }
    cout << endl;
}

class Solution {
    public:
        unordered_map<int, UndirectedGraphNode*> h;
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
            if (!node) return nullptr;
            UndirectedGraphNode* nd = nullptr;
            if (!h[node->label]) h[node->label] = new UndirectedGraphNode {node->label};
            nd = h[node->label];
            for (auto& p: node->neighbors) {
                if (!h[p->label]) nd->neighbors.push_back(cloneGraph(p));
                else nd->neighbors.push_back(h[p->label]);
            }

            return nd;
        }
};

void test(UndirectedGraphNode* nd) 
{
    cout << "origin: ";
    dump(nd);
    auto* nd2 = Solution().cloneGraph(nd);
    cout << "cloned: ";
    dump(nd2);
}


int main(int argc, char const *argv[])
{
    {
        UndirectedGraphNode n0 {0};
        UndirectedGraphNode n1 {1};
        UndirectedGraphNode n2 {2};
        n0.neighbors.push_back(&n1);
        n0.neighbors.push_back(&n2);
        n1.neighbors.push_back(&n2);
        n2.neighbors.push_back(&n2);
        test(&n0);
    }
    return 0;
}
