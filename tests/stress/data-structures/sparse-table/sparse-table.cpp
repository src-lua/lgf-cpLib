#include <bits/stdc++.h>
using namespace std;
#include "lib/data-structures/sparse-table/sparse-table.hpp"

struct MinNode {
    int v = INT_MAX; MinNode(int x = INT_MAX) : v(x) {}
    static MinNode merge(const MinNode& a, const MinNode& b) { return MinNode(min(a.v, b.v)); }
};

int main() {
    mt19937 rng(14);
    for (int t = 0; t < 500; t++) {
        int n = 1 + rng() % 50;
        vector<int> a(n); vector<MinNode> v(n);
        for (int i = 0; i < n; i++) { a[i] = rng() % 1000; v[i] = MinNode(a[i]); }
        SparseTable<MinNode> st(v);
        for (int q = 0; q < 100; q++) {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            int mn = INT_MAX; for (int i = l; i <= r; i++) mn = min(mn, a[i]);
            assert(st.query(l, r).v == mn);
        }
    }
    puts("sparse-table: RMQ vs brute, 500 casos");
    return 0;
}
