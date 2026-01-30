#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

/* Dynamic Segment Tree with Lazy Propagation (Range Update, Range Query)
 * Utilizada para intervalos gigantes (ex: 0 a 10^18).
 * Complexidade: O(log N) por operação.
 * Memória: O(Q log N) onde Q é o número de operações.
 * Requisitos:
 * - NODE deve ter: static merge(const NODE&, const NODE&),
 *   apply(const TAG&, ll, ll) e construtor identidade.
 * - TAG deve ter: apply(const TAG&), campo 'has' (bool) e
 *   construtor identidade.
 */

/* --- Exemplo de NODE e TAG ---
struct Tag {
    ll add = 0;
    bool has = false;
    void apply(const Tag& t) {
        add += t.add;
        has = true;
    }
};

struct Node {
    ll val = 0;
    static Node merge(const Node& l, const Node& r) {
        return {l.val + r.val};
    }
    void apply(const Tag& t, ll l, ll r) {
        val += t.add * (r - l + 1);
    }
};
*/

template<typename NODE, typename TAG>
struct DynamicSegTree {
    struct InternalNode {
        NODE node;
        TAG tag;
        int l, r;
        InternalNode() : node(NODE()), tag(TAG()), l(-1), r(-1) {}

        void apply(const TAG& t, ll l, ll r) {
            node.apply(t, l, r);
            tag.apply(t);
        }
    };

    ll L, R;
    vector<InternalNode> seg;

    DynamicSegTree(ll l, ll r) : L(l), R(r) {
        seg.emplace_back();
    }

    void push(int v, ll l, ll r) {
        if (!seg[v].tag.has) return;
        if (l == r) return seg[v].tag = TAG();

        if (seg[v].l == -1) { seg[v].l = seg.size(); seg.emplace_back(); }
        if (seg[v].r == -1) { seg[v].r = seg.size(); seg.emplace_back(); }

        ll mid = l + (r - l) / 2;
        seg[seg[v].l].apply(seg[v].tag, l, mid);
        seg[seg[v].r].apply(seg[v].tag, mid+1, r);
        
        seg[v].tag = TAG();
    }

    void update(int v, ll l, ll r, ll ql, ll qr, const TAG& t) {
        if (ql <= l && r <= qr) return seg[v].apply(t, l, r);
        
        push(v, l, r);
        ll mid = l + (r - l) / 2;
        if (ql <= mid) {
            if (seg[v].l == -1) { seg[v].l = seg.size(); seg.emplace_back(); }
            update(seg[v].l, l, mid, ql, qr, t);
        }
        if (qr > mid) {
            if (seg[v].r == -1) { seg[v].r = seg.size(); seg.emplace_back(); }
            update(seg[v].r, mid + 1, r, ql, qr, t);
        }
        
        NODE left = (seg[v].l != -1) ? seg[seg[v].l].node : NODE();
        NODE rght = (seg[v].r != -1) ? seg[seg[v].r].node : NODE();
        seg[v].node = NODE::merge(left, rght);
    }

    NODE query(int v, ll l, ll r, ll ql, ll qr) {
        if (v == -1 || ql > r || qr < l) return NODE();
        if (ql <= l && r <= qr) return seg[v].node;
        push(v, l, r);
        ll mid = l + (r - l) / 2;
        return NODE::merge(query(seg[v].l, l, mid, ql, qr),
                           query(seg[v].r, mid + 1, r, ql, qr));
    }

    void update(ll ql, ll qr, const TAG& t) { update(0, L, R, ql, qr, t); }
    NODE query(ll ql, ll qr) { return query(0, L, R, ql, qr); }
};