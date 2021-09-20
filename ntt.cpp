#include <cassert>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <queue>

uint32_t rd() {
	uint32_t a = 0;
	for (; ; ) {
		char c = getchar();
		if (c < '0')
			return a;
		a = a * 10 + c - '0';
	}
}

template<uint32_t mod>
struct shortMint {
	uint32_t v;
	constexpr inline shortMint(uint32_t v = 0) : v(v) {}
	constexpr inline shortMint operator+(shortMint rhs) const {
		uint32_t r = v + rhs.v;
		return r < mod ? r : r - mod;
	}
	constexpr inline shortMint operator-(shortMint rhs) const {
		uint32_t r = v - rhs.v;
		return r < mod ? r : r + mod;
	}
	constexpr inline shortMint operator-() const {
		return v ? mod - v : 0;
	}
	constexpr inline shortMint operator*(shortMint rhs) const {
		return (uint64_t) v * rhs.v % mod;
	}
	constexpr inline shortMint& operator+=(shortMint rhs) {
		v += rhs.v;
		if (v >= mod)
			v -= mod;
		return *this;
	}
	constexpr inline shortMint& operator-=(shortMint rhs) {
		v -= rhs.v;
		if (v >= mod)
			v += mod;
		return *this;
	}
	constexpr inline shortMint& operator*=(shortMint rhs) {
		v = (uint64_t) v * rhs.v % mod;
		return *this;
	}
	constexpr inline bool operator==(shortMint rhs) const {
		return v == rhs.v;
	}
	constexpr inline bool operator!=(shortMint rhs) const {
		return v != rhs.v;
	}
	constexpr inline shortMint operator^(uint32_t rhs) const {
		shortMint r = 1, b = *this;
		while (rhs) {
			if (rhs & 1)
				r *= b;
			b *= b;
			rhs >>= 1;
		}
		return r;
	}
};
using mint = shortMint<998244353>;

template<bool inv = false>
void ntt(std::vector<mint>& p) {
	assert(!p.empty());
	uint32_t n = p.size();
	if (n == 1)
		return;
	assert(n == (n & -n));
	uint32_t lgn = __builtin_ctz(n);
	for (uint32_t i = 0, j = 0; i < n; i++) {
		if (i < j)
			std::swap(p[i], p[j]);
		for (uint32_t k = n >> 1; ~(j ^= k) & k; k >>= 1);
	}
	/*
		modulus: 998244353 = 2^23 * 119 + 1
		primitive root: 3
		3 ^ 119: 15311432
		15311432 ^ -1 = 469870224
	*/
	mint powers[n >> 1];
	powers[0] = 1;
	powers[1] = mint(inv ? 469870224 : 15311432) ^ (1u << 23 - lgn);
	for (uint32_t i = 2; i < n >> 1; i++)
		powers[i] = powers[i - 1] * powers[1];
	for (uint32_t i = 0; i < lgn; i++) {
		for (uint32_t j = 0; j < n; j += 2u << i) {
			for (uint32_t k = 0; k < uint32_t(1) << i; k++) {
				mint& top = p[j + k], & bottom = p[(1u << i) + j + k];
				bottom = top - bottom * powers[(n >> i + 1) * k];
				top = top + top - bottom;
			}
		}
	}
	if constexpr (inv) {
		mint invn = mint(499122177) ^ lgn;
		for (mint& i : p)
			i *= invn;
	}
}

std::vector<mint> convolution(std::vector<mint> p, std::vector<mint> q) {
	if (p.empty() || q.empty())
		return {};
	uint32_t n = p.size() + q.size() - 1;
	while (n != (n & -n))
		n += n & -n;
	p.resize(n, 0);
	q.resize(n, 0);
	ntt(p);
	ntt(q);
	for (uint32_t i = 0; i < n; i++)
		p[i] *= q[i];
	ntt<true>(p);
	while (!p.empty() && p.back() == 0)
		p.pop_back();
	return p;
}

int main() {
	uint32_t n = rd(), m = rd();
	std::vector<mint> a(n), b(m);
	for (auto& i : a)
		i = rd();
	for (auto& i : b)
		i = rd();
	auto c = convolution(a, b);
	c.resize(n + m - 1, 0);
	for (uint32_t i = 0; i < c.size(); i++)
		printf("%u%c", c[i], " \n"[i == c.size() - 1]);
}