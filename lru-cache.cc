#include <iostream>
#include <unordered_map>
#include <cassert>
#include <climits>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

template<class T, class U>
ostream& operator<<(ostream& os, const unordered_map<T, U>& v)
{
    os << "{";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << "(" << x.first << ":" << x.second->val <<")";
    }
    return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << x;
    }
    return os << "]";
}

class LRUCache {
    public:
        struct Node {
            int key {0};
            int val {0};
            Node* prev {nullptr};
            Node* next {nullptr};
        };

        LRUCache(int capacity) {
            _cap = capacity;
            head.next = &head;
            head.prev = &head;
        }

        int get(int key) {
            if (_m.find(key) == _m.end()) {
                return -1;
            }

            //rearrange
            promote(key);
            return _m[key]->val;
        }

        void set(int key, int value) {
            Node* n = nullptr;

            if (_m.find(key) != _m.end()) {
                promote(key);
                _m[key]->val = value;
                return;

            } else if (_m.size() == _cap) {
                auto d = head.prev;
                _m.erase(_m.find(d->key));
                d->prev->next = d->next;
                d->next->prev = d->prev;
                n = d;
            } else n = new Node;

            n->key = key;
            n->val = value;
            _m[key] = n;

            n->next = head.next;
            head.next->prev = n;
            n->prev = &head;
            head.next = n;
        }

        int _cap;
        unordered_map<int, Node*> _m;
        Node head; // dummy head

        void promote(int key) {
            auto* n = _m[key];

            n->prev->next = n->next;
            n->next->prev = n->prev;

            n->next = head.next;
            head.next->prev = n;
            n->prev = &head;
            head.next = n;
        }
};

ostream& dump(ostream& os, const LRUCache& lru) {
    auto& h = lru.head;
    auto* p = h.next;
    os << "list: ";
    while (p != &h) {
        os << "(" << p->key << ": " << p->val << ")";
        p = p->next;
    }
    os << endl;
    os << "map: " << lru._m;
    return os << endl;
}


void test()
{
    LRUCache lru(10); 
    assert(lru.get(100) == -1);
    lru.set(100, 20);
    dump(cout, lru);

    assert(lru.get(100) != -1);
    assert(lru.get(100) == 20);
    for (int i = 0; i < 10; i++) {
        lru.set(i, i);
    }
    assert(lru.get(100) == -1);
    lru.set(9, 900); // promote key 9
    lru.set(10, 10);
    assert(lru.get(0) == -1); // key 0 became the last
    dump(cout, lru);

    lru.set(1, 100);
    lru.set(12, 120);
    lru.set(5, 500);
    dump(cout, lru);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
