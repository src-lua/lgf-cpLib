const int max_size = 2e5+5;
vector<ll> arr(max_size+1,0);
vector<ll> bit(max_size+1,0);

int n, q;

// Time complexity: O(log(n))
ll query(int i) { // [1,i]
	ll ret = 0;
	for(; i > 0; i -= i & -i) {
		ret += bit[i];
	}
	return ret;
}

// Time complexity: O(log(n))
ll queryRange(int l, int r) { // [l,r]
	ll qr = query(r);
	ll ql = query(l-1);
	return qr-ql;
}

// Time complexity: O(log(n))
void increment(ll index, ll value) {     
	for(; index <= n; index += index & -index) {
		bit[index] += value;
	}
}

// Time complexity: O(n * log(n))
void build(const vector<ll>& nums) {
	for(int i = 0; i < nums.size(); i++) {
		increment(i+1,nums[i]);
	}
}