// Time Complexity: O(log(min(m, n)))
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Time Complexity: O(log(min(m, n)))
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }