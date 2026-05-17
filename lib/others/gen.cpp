#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int x = rng();

int uniform(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}