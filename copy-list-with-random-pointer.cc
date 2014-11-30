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

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

ostream& operator<<(ostream& os, RandomListNode* l)
{
    while (l) {
        os << l->label << " ";
        l = l->next;
    }

    return os << "$";
}

class Solution3 {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode* p = head;
        RandomListNode dummy {0};
        RandomListNode* res = &dummy;
        while (p) {
            auto* t = new RandomListNode {p->label};
            t->next = p->next;
            p->next = t;
            p = t->next;
        }

        p = head;
        while (p) {
            if (p->random)
                p->next->random = p->random->next;
            p = p->next->next;
        }

        p = head;
        if (p) { dummy.next = p->next; res = p->next; }
        while (p) {
            p->next = p->next->next;
            if (res->next) res->next = res->next->next;
            p = p->next;
            res = res->next;
        }

        return dummy.next;
    }
};

//OJ dont allow modification of original list,
//so this two-pass solution fails submit
class Solution2 {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode* p = head;
        RandomListNode dummy {0};
        RandomListNode* res = &dummy;
        while (p) {
            res->next = new RandomListNode {p->label};
            res->next->random = p->random;

            auto* pp = p;
            p = p->next;
            pp->next = res->next;
            res = res->next;
        }

        res = dummy.next;
        while (res) {
            if (res->random) res->random = res->random->next;
            res = res->next;
        }
        return dummy.next;
    }
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        // old <-> new
        unordered_map<RandomListNode*, RandomListNode*> rel;
        RandomListNode* p = head;
        RandomListNode dummy {0};
        RandomListNode* res = &dummy;
        while (p) {
            if (rel.find(p) != rel.end()) {
                res->next = rel[p];
            } else {
                res->next = new RandomListNode {p->label};
            }
            
            if (p->random) {
                if (rel.find(p->random) == rel.end()) {
                    rel[p->random] = new RandomListNode {p->random->label};
                }
                res->next->random = rel[p->random];
            }
            
            p = p->next;
            res = res->next;
        }

        return dummy.next;
    }
};

void test(RandomListNode* l) {
	auto* t = Solution3().copyRandomList(l);
    while (t) {
        cout << t->label << ":" << (t->random?t->random->label:0) << " ";
        t = t->next;
    }
}

int main(int argc, char const *argv[])
{
    {
        RandomListNode n {1};
        RandomListNode n1 {2};
        RandomListNode n2 {3};
        RandomListNode n3 {4};
        RandomListNode n4 {5};
        n.next = &n1; n1.next = &n2; n2.next = &n3; n3.next = &n4;
        n.random = &n2;
        n2.random = &n4;
        n4.random = &n1;
        test(&n);
    }
    return 0;    
}
