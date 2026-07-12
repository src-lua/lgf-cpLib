#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/sieve.hpp"

vector<pair<int,int>> brute_factor(int x) {
    vector<pair<int,int>> f;
    for (int p = 2; (long long)p * p <= x; p++)
        if (x % p == 0) { int e = 0; while (x % p == 0) { x /= p; e++; } f.push_back({p, e}); }
    if (x > 1) f.push_back({x, 1});
    return f;
}
vector<int> brute_div(int x) {
    vector<int> d;
    for (int i = 1; i <= x; i++) if (x % i == 0) d.push_back(i);
    return d;
}

int main() {
    int N = 100000;
    auto spf = spf_sieve(N);
    for (int x = 2; x <= N; x++) {
        assert(factor(x, spf) == brute_factor(x));
        auto d = divisors(x, spf); sort(d.begin(), d.end());
        assert(d == brute_div(x));
    }
    // sieve() de primos vs spf
    auto pr = sieve(N);
    for (int p : pr) assert(spf[p] == p);
    puts("sieve: factor + divisors + primos vs brute, 2..100k");
    return 0;
}
