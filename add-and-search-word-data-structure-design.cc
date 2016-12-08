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
class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void addWord(string word) {
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

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return doSearch(root, word, 0);
    }

private:
    TrieNode* root;

    bool doSearch(TrieNode* t, const string& word, int i) {
        if (i == word.size()) {
            return (t->end);
        }

        auto* p = t->children;
        if (word[i] == '.') {
            for (int j = 0; j < 26; j++) {
                if (p[j] && doSearch(p[j], word, i+1))
                    return true;
            }
        } else {
            if (!p[ORD(word[i])])
                return false;
            return doSearch(p[ORD(word[i])], word, i+1);
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    WordDictionary wd;

    wd.addWord("bad"); //
    wd.addWord("dad"); //
    wd.addWord("mad"); //

    assert (wd.search("pad") == false); // -> false
    assert (wd.search("bad") == true); // -> true
    assert (wd.search(".ad") == true); // -> true
    assert (wd.search("b..") == true); // -> true
    assert (wd.search("b...") == false);
	return 0;
}
