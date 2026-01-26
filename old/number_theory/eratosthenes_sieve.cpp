vector<ll> prime_list;

// Time Complexity: O(n log log n)
void EratosthenesSieve(ll n) {
    vector<bool> prime(n + 1, true);
 
    for (ll p = 2; p <= n; p++) {
        if (prime[p] == true) {
            prime_list.push_back(p);

            for (ll i = p; i <= n; i += p)
                prime[i] = false;
        }
    }
}