#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Trie (Prefix Tree)
 * Inserção e busca de strings em O(|s|).
 * Memória: O(N * ALPHA) onde N é o total de caracteres inseridos.
 * Requisitos: strings sobre o alfabeto [base, base + ALPHA).
 */

template<int ALPHA = 26, char BASE = 'a'>
struct Trie {
    struct Node {
        int ch[ALPHA];
        int cnt;
        int end;
        Node() : cnt(0), end(0) { fill(ch, ch + ALPHA, -1); }
    };

    vector<Node> t;

    Trie() { t.emplace_back(); }

    void insert(const string& s) {
        int no = 0;
        for (char c : s) {
            int b = c - BASE;
            if (t[no].ch[b] == -1) {
                t[no].ch[b] = t.size();
                t.emplace_back();
            }
            no = t[no].ch[b];
            t[no].cnt++;
        }
        t[no].end++;
    }

    bool search(const string& s) const {
        int no = 0;
        for (char c : s) {
            int b = c - BASE;
            if (t[no].ch[b] == -1) return false;
            no = t[no].ch[b];
        }
        return t[no].end > 0;
    }

    int count_prefix(const string& s) const {
        int no = 0;
        for (char c : s) {
            int b = c - BASE;
            if (t[no].ch[b] == -1) return 0;
            no = t[no].ch[b];
        }
        return t[no].cnt;
    }

    int count(const string& s) const {
        int no = 0;
        for (char c : s) {
            int b = c - BASE;
            if (t[no].ch[b] == -1) return 0;
            no = t[no].ch[b];
        }
        return t[no].end;
    }
};
