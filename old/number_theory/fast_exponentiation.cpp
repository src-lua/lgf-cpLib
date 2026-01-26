const ll MOD = 1e9+7;

class Matrix{ 
	public:
	vector<vector<ll>> mat;
	int m;
	Matrix(int m): m(m) {
		mat.resize(m);
		for(int i = 0; i < m; i++) mat[i].resize(m,0);
	}
	Matrix operator * (const Matrix& rhs) {
		Matrix ans = Matrix(m);
		for(int i = 0; i < m; i++)
			for(int j = 0; j < m; j++)
				for(int k = 0; k < m; k++)
					ans.mat[i][j] = (ans.mat[i][j] + (mat[i][k] * rhs.mat[k][j]) % MOD) % MOD;
		return ans;
	}
};

Matrix fexp(Matrix a, ll n) {
	int m = a.m;
	Matrix ans = Matrix(m);
	for(int i = 0; i < m; i++) ans.mat[i][i] = 1;
	while(n) {
		if(n & 1) ans = ans * a;
		a = a * a;
		n >>= 1;
	}
	return ans;
}

// Time complexity: O(log(n))
ll fexpll(ll a, ll n) {
	ll ans = 1;
	while(n) {
		if(n & 1) ans = (ans * a) % MOD;
		a = (a * a) % MOD;
		n >>= 1;
	}
	return ans;
}

// Time complexity: O(log(mod-2))
ll modInverse(ll n) {
    fexpll(n, MOD-2);
}