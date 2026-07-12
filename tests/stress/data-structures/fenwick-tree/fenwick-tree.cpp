#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/data-structures/fenwick-tree/fenwick-tree.hpp"

struct Node {
    ll val = 0; Node(ll v = 0) : val(v) {}
    void operator+=(const Node& o) { val += o.val; }
    Node operator-(const Node& o) const { return Node(val - o.val); }
};

int main() {
    mt19937 rng(15);
    for (int t = 0; t < 500; t++) {
        int n = 1 + rng() % 40;
        vector<ll> a(n, 0);
        FenwickTree<Node> ft(n);
        for (int q = 0; q < 200; q++) {
            if (rng() % 2) { int i = rng() % n; ll v = (ll)(rng() % 100) - 50; a[i] += v; ft.update(i, Node(v)); }
            else { int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                ll s = 0; for (int i = l; i <= r; i++) s += a[i]; assert(ft.query(l, r).val == s); }
        }
    }
    puts("fenwick-tree: point-update / range-sum vs brute, 500 casos");
    return 0;
}
