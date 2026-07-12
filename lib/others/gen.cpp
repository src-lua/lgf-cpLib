#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

auto seed =
  chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(seed);
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
