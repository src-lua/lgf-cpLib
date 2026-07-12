#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/data-structures/segment-tree/segment-tree.hpp"
#include "lib/data-structures/segment-tree/lazy-segment-tree.hpp"

struct SNode {
    ll val = 0; SNode(ll v = 0) : val(v) {}
    static SNode merge(const SNode& a, const SNode& b) { return SNode(a.val + b.val); }
    void apply(ll v) { val = v; }
};
struct LTag { ll add = 0; void compose(const LTag& t) { add += t.add; } };
struct LNode {
    ll val = 0; LNode(ll v = 0) : val(v) {}
    static LNode merge(const LNode& a, const LNode& b) { return LNode(a.val + b.val); }
    void apply(const LTag& t, int l, int r) { val += t.add * (r - l + 1); }
};

int main() {
    mt19937 rng(6);
    // SegTree: point set, range sum
    for (int t = 0; t < 300; t++) {
        int n = 1 + rng() % 40;
        vector<ll> a(n); for (auto& x : a) x = rng() % 100;
        SegTree<SNode> st(a);
        for (int q = 0; q < 200; q++) {
            if (rng() % 2) { int i = rng() % n; ll v = rng() % 100; a[i] = v; st.update(i, v); }
            else { int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                ll s = 0; for (int i = l; i <= r; i++) s += a[i]; assert(st.query(l, r).val == s); }
        }
    }
    // Lazy: range add, range sum
    for (int t = 0; t < 300; t++) {
        int n = 1 + rng() % 40;
        vector<ll> a(n); for (auto& x : a) x = rng() % 100;
        LazySegmentTree<LNode, LTag> st(a);
        for (int q = 0; q < 200; q++) {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            if (rng() % 2) { ll v = rng() % 50; st.update(l, r, {v}); for (int i = l; i <= r; i++) a[i] += v; }
            else { ll s = 0; for (int i = l; i <= r; i++) s += a[i]; assert(st.query(l, r).val == s); }
        }
    }
    puts("segment-tree: seg (point/sum) + lazy (range-add/sum) vs brute");
    return 0;
}
