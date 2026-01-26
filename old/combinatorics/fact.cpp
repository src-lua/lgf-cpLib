// Time complexity: O(n)
ll fact (ll n) {
    ll answ = 1;
    for (int i = 2; i <= n; i++) {
        answ  = (answ * i) % MOD;
    }
    return answ % MOD;
    
}