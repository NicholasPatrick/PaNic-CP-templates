#include <climits>
#include <cstdint>
#include <initializer_list>
#include <queue>

uint64_t modmul(uint64_t a, uint64_t b, uint64_t m) {
	return (__uint128_t) a * b % m;
}
bool mr(uint32_t d, uint8_t r, uint32_t base) {
	uint32_t n = d << r | 1;
	assert(d & 1);
	uint32_t x = 1;
	while (d) {
		if (d & 1)
			x = (uint64_t)x * base % n;
		base = (uint64_t)base * base % n;
		d >>= 1;
	}
	if (x == 1)
		return true;
	while (--r && x != n - 1)
		x = (uint64_t)x * x % n;
	return x == n - 1;
}
bool mrll(uint64_t d, uint8_t r, uint64_t base) {
	uint64_t n = d << r | 1;
	assert(d & 1);
	uint64_t x = 1;
	while (d) {
		if (d & 1)
			x = modmul(x, base, n);
		base = modmul(base, base, n);
		d >>= 1;
	}
	if (x == 1)
		return true;
	while (--r && x != n - 1)
		x = modmul(x, x, n);
	return x == n - 1;
}
template<bool smallTests = true>
bool prime_test(uint64_t n) {
	if constexpr (smallTests) {
		if (n == 2 || n == 3 || n == 5 || n == 7)
			return true;
		if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0)
			return false;
		if (n < 121)
			return true;
	}
	if (n <= UINT32_MAX) {
		uint32_t d = n - 1;
		uint8_t r = __builtin_ctz(d);
		d >>= r;
		std::vector<uint32_t> bases = {2, 7, 61};
		for (auto a : bases) {
			if (!mr(d, r, a))
				return false;
		}
		return true;
	} else {
		uint64_t d = n - 1;
		uint8_t r = __builtin_ctz(d);
		d >>= r;
		std::vector<uint64_t> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
		for (auto a : bases) {
			if (!mrll(d, r, a))
				return false;
		}
	}
	return true;
}