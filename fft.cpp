#include <cassert>
#include <complex>
#include <cstdint>
#include <queue>

const double pi = acos(-1), tau = pi * 2;
using cd = std::complex<double>;
template<bool inv = false>
std::vector<cd> fft(std::vector<cd> p) {
	assert(!p.empty());
	uint32_t n = p.size();
	if (n == 1)
		return p;
	assert(n == (n & -n));
	uint32_t lgn = __builtin_ctz(n);
	for (uint32_t i = 0, j = 0; i < n; i++) {
		if (i < j)
			std::swap(p[i], p[j]);
		for (uint32_t k = n >> 1; ~(j ^= k) & k; k >>= 1);
	}
	cd powers[n >> 1];
	if constexpr (inv) {
		for (uint32_t i = 0; i < n >> 1; i++)
			powers[i] = cd(cos(tau * i / n), sin(tau * i / n));
	} else {
		for (uint32_t i = 0; i < n >> 1; i++)
			powers[i] = cd(cos(tau * i / n), sin(-tau * i / n));
	}
	for (uint32_t i = 0; i < lgn; i++) {
		for (uint32_t j = 0; j < n; j += 2 << i) {
			for (uint32_t k = 0; k < 1 << i; k++) {
				cd &top = p[j + k], &bottom = p[(1u << i) + j + k];
				bottom = top - bottom * powers[(n >> i + 1) * k];
				top = top + top - bottom;
			}
		}
	}
	if constexpr (inv) {
		for (cd& i : p)
			i /= n;
	}
	return p;
}