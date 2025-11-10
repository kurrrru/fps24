#include <bits/stdc++.h>
using namespace std;

template <typename T>
T ext_gcd(T a, T b, T &x, T &y)
{
	assert(a != 0 || b != 0);
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	T d = ext_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

template <typename T>
T inv_mod(T a, T mod)
{
	assert(mod > 0);
	assert(a != 0);
	T x, y;
	ext_gcd(a, mod, x, y);
	return (mod + x % mod) % mod;
}

template <typename T>
std::vector<T> factorial_mod(T n, T mod) {
	assert(n >= 0);
	assert(mod > 0);
	std::vector<T> fact(n + 1, 1);
	for (T i = 1; i <= n; i++)
		fact[i] = (fact[i - 1] * i) % mod;
	return fact;
}

template <typename T>
std::vector<T> factorial_inv_mod(T n, T mod)
{
	assert(n >= 0);
	assert(mod > 0);
	std::vector<T> fact_inv(n + 1, 1);
	std::vector<T> fact(n + 1, 1);
	for (T i = 1; i <= n; i++)
		fact[i] = (fact[i - 1] * i) % mod;
	fact_inv[n] = inv_mod(fact[n], mod);
	for (T i = n - 1; i >= 0; i--)
		fact_inv[i] = (fact_inv[i + 1] * (i + 1)) % mod;
	return fact_inv;
}

template <typename T>
T combination_mod(T n, T k, T mod, const std::vector<T> &fact, const std::vector<T> &fact_inv) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    if (k > n) return 0;
	assert(n >= 0);
	assert(n < fact.size());
	assert(k < fact_inv.size() && n - k < fact_inv.size());
	return (fact[n] * fact_inv[k] % mod) * fact_inv[n - k] % mod;
}

int main() {
    long long N, M;
    cin >> N >> M;
    const long long MOD = 998244353;

    auto fact = factorial_mod(max(N, M) + 1, MOD);
    auto fact_inv = factorial_inv_mod(max(N, M) + 1, MOD);

    long long result = 0;
    for (long long k = 0; k <= M - N + 1; k++) {
        result += combination_mod(N + k, N, MOD, fact, fact_inv) *
                  combination_mod(M - k - 1, M - N + 1 - k, MOD, fact, fact_inv) % MOD *
                  ((M - N + 1 - k) % 2 == 0 ? 1 : MOD - 1) % MOD;
        result %= MOD;
    }
    result *= fact[N];
    result %= MOD;
    cout << result << endl;
}