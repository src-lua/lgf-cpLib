#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Fenwick Tree 2D Sparse (Point Update, Rectangle Query)
 * Suporta coordenadas até 10^9 usando compressão interna.
 * Complexidade: Build O(P log P), Update/Query O(log^2 P).
 * Memória: O(P log P).
 * Requisitos:
 * - NODE deve ter: operator+=, operator-, operator+ e construtor default.
 * - Offline: Todos os pontos de interesse devem ser passados no build.
 *
 * Créditos: Adaptado de TFG (Thiago Ferreira Gonçalves)
 * Fonte: github.com/tfg50/Competitive-Programming
 */

/* --- Exemplo de NODE (Soma com Inclusão-Exclusão) ---
struct Node {
    ll val;
    Node(long long v = 0) : val(v) {}

    void operator+=(const Node& other) {
        val += other.val;
    }

    Node operator-(const Node& other) const {
        return Node(val - other.val);
    }

    Node operator+(const Node& other) const {
        return Node(val + other.val);
    }
};
*/

template<typename NODE>
struct FenwickTree2DSparse {
    using pii = pair<int, int>;
    vector<int> ord;
    vector<vector<NODE>> bit;
    vector<vector<int>> coord;

    FenwickTree2DSparse(vector<pii> pts) {
        sort(pts.begin(), pts.end());
        for (auto [x, y] : pts) {
            if (ord.empty() || x != ord.back()) ord.push_back(x);
        }

        bit.resize(ord.size() + 1);
        coord.resize(ord.size() + 1);

        sort(pts.begin(), pts.end(), [](const pii& a, const pii& b) {
            return a.second < b.second;
        });

        for (auto [x, y] : pts) {
            for (int i = get_x(x); i < (int)bit.size(); i += i & -i) {
                if (coord[i].empty() || coord[i].back() != y)
                    coord[i].push_back(y);
            }
        }

        for (int i = 0; i < (int)bit.size(); i++) {
            bit[i].assign(coord[i].size() + 1, NODE());
        }
    }

    inline int get_x(int x) {
        return upper_bound(ord.begin(), ord.end(), x) - ord.begin();
    }

    inline int get_y(int i, int y) {
        return upper_bound(coord[i].begin(), coord[i].end(), y)
               - coord[i].begin();
    }

    void update(int x, int y, NODE v) {
        for (int i = get_x(x); i < (int)bit.size(); i += i & -i) {
            for (int j = get_y(i, y); j < (int)bit[i].size(); j += j & -j) {
                bit[i][j] += v;
            }
        }
    }

    NODE query(int x, int y) {
        NODE res;
        for (int i = get_x(x); i > 0; i -= i & -i) {
            for (int j = get_y(i, y); j > 0; j -= j & -j) {
                res += bit[i][j];
            }
        }
        return res;
    }

    NODE query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2)
               - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};