#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/miller-rabin.hpp"

int main() {
    int N = 200000;
    vector<bool> comp(N + 1, false);
    for (int i = 2; (ll)i * i <= N; i++) if (!comp[i]) for (int j = i * i; j <= N; j += i) comp[j] = true;
    for (int n = 2; n <= N; n++) assert(is_prime(n) == !comp[n]);
    assert(is_prime(1000000007LL) && is_prime(998244353LL));
    assert(!is_prime(1000000005LL) && !is_prime((ll)1000003 * 1000033));

    mt19937_64 rng(3);
    for (int t = 0; t < 3000; t++) {
        ll n = 1 + rng() % 1000000000000LL;
        auto f = factorize(n);
        ll prod = 1; for (ll p : f) { assert(is_prime(p)); prod *= p; }
        assert(prod == n);
    }
    puts("miller-rabin: is_prime 2..200k + factorize 3k (ate 1e12)");
    return 0;
}
