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
#include <cassert>

using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
    }

	TrieNode* children[26] {nullptr,};
    bool end {false}; 
};

#define ORD(ch) ((ch) - 'a')
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        auto *t = root;
        auto p = word.cbegin();
        while (p != word.cend()) {
            if (!t->children[ORD(*p)])
                t->children[ORD(*p)] = new TrieNode();
            t = t->children[ORD(*p)];
            p++;
        }
        t->end = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        auto *t = root;
        auto p = word.cbegin();
        while (p != word.cend()) {
            if (!t->children[ORD(*p)])
                return false;
            t = t->children[ORD(*p)];
            p++;
        }

        return (t->end);
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        auto *t = root;
        auto p = prefix.cbegin();
        while (p != prefix.cend()) {
            if (!t->children[ORD(*p)])
                return false;
            t = t->children[ORD(*p)];
            p++;
        }

        return true;
    }

private:
    TrieNode* root;
};


int main(int argc, char *argv[])
{
	Trie trie;
	trie.insert("algo");
	trie.insert("algorithm");
	trie.insert("baby");
	trie.insert("bad");
	trie.insert("bachelor");
    assert(trie.search("algo") == true);
    assert(trie.startsWith("ba") == true);
    assert(trie.startsWith("algo") == true);
    assert(trie.startsWith("algorith") == true);

	return 0;
}
