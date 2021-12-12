#include <cstdint>
#include <cstdio>
#include <type_traits>

template<typename T>
constexpr T inv_int(T n) {
	static_assert(std::is_integral_v<T>);
	T r = n ^ (n << 1 ^ n << 2) & 8;
	r *= 2 - n * r;
	if constexpr (sizeof(T) >= 2)
		r *= 2 - n * r;
	if constexpr (sizeof(T) >= 3)
		r *= 2 - n * r;
	if constexpr (sizeof(T) >= 5)
		r *= 2 - n * r;
	if constexpr (sizeof(T) >= 9)
		r *= 2 - n * r;
	return r;
}
using int128_t = __int128_t;
using uint128_t = __uint128_t;
template<uint64_t mod>
class montgomery {
	// guarantees v is always in [0, mod)
	static_assert(mod & 1, "modulus must be odd");
	static_assert(mod < 0x8000000000000000, "modulus must fit in 63 bits");
	using T1 = std::conditional_t<(mod < 0x80000000), uint32_t, uint64_t>;
	using T2 = std::conditional_t<(mod < 0x80000000), uint64_t, uint128_t>;
	using S1 = std::make_signed<T1>;
	using S2 = std::make_signed<T2>;
	template<typename S1>
	static constexpr S1 inv_normal(S1 n) {
		S1 w = 1, x = 0, y = m;
		while (n != 1) {
			S1 z = y / n;
			y -= n * z;
			x -= w * z;
			std::swap(y, n);
			std::swap(w, x);
		}
		return w < 0 ? w + m : w;
	}
	static const T1 m = mod;
	static constexpr T1 get_r() {
		return (T1)-1 % m + 1;
	}
	static const T1 r = get_r();
	static constexpr T1 get_r2() {
		return (T2)-1 % m + 1;
	}
	static const T1 r2 = get_r2();
	static constexpr T1 get_r3() {
		return ((T2)r2 << 32) % m;
	}
	static const T1 r3 = get_r3();
	static constexpr T1 get_nim() {
		return -inv_int(m);
	}
	static const T1 nim = get_nim();
	static constexpr T1 reduce(T2 a) {
		return (a + (T1)a * nim * (T2)m) >> sizeof(T1) * 8;
	}
	static constexpr T1 reduce2(T2 a) {
		T1 r = (a + (T1)a * nim * (T2)m) >> sizeof(T1) * 8;
		return r < m ? r : r - m;
	}
	T1 v;
public:
	montgomery() : v(0) {}
	montgomery(T1 init) : v(reduce2((T2)r2 * init)) {}
	T1 eval() {
		return reduce(v);
	}
	montgomery& operator+=(montgomery rhs) {
		v += rhs.v;
		if (v >= m)
			v -= m;
		return *this;
	}
	montgomery& operator-=(montgomery rhs) {
		v -= rhs.v;
		if (v >= m)
			v += m;
		return *this;
	}
	montgomery& operator*=(montgomery rhs) {
		v = reduce2((T2)v * rhs.v);
		return *this;
	}
	montgomery& operator/=(montgomery rhs) {
		v = reduce2((T2)v * reduce((T2)r3 * inv_normal(rhs.v)));
		return *this;
	}
	montgomery operator+(montgomery rhs) const {
		auto ret = *this;
		return ret += rhs;
	}
	montgomery operator-(montgomery rhs) const {
		auto ret = *this;
		return ret -= rhs;
	}
	montgomery operator*(montgomery rhs) const {
		auto ret = *this;
		return ret *= rhs;
	}
	montgomery operator/(montgomery rhs) const {
		auto ret = *this;
		return ret /= rhs;
	}
	montgomery operator-() const {
		auto ret = *this;
		if (ret.v)
			ret.v = m - ret.v;
		return ret;
	}
	montgomery operator+() const {
		return *this;
	}
	montgomery& operator++() {
		v += r;
		if (v >= m)
			v -= m;
		return *this;
	}
	montgomery& operator--() {
		v -= r;
		if (v >= m)
			v += m;
		return *this;
	}
	montgomery operator++(int) {
		auto ret = *this;
		operator++();
		return ret;
	}
	montgomery operator--(int) {
		auto ret = *this;
		operator--();
		return ret;
	}
	bool operator==(montgomery rhs) const {
		return v == rhs.v;
	}
	bool operator!=(montgomery rhs) const {
		return v != rhs.v;
	}
	bool operator<(montgomery rhs) const {
		return v < rhs.v;
	}
	bool operator>(montgomery rhs) const {
		return v > rhs.v;
	}
	bool operator<=(montgomery rhs) const {
		return v <= rhs.v;
	}
	bool operator>=(montgomery rhs) const {
		return v >= rhs.v;
	}
};
template<uint64_t mod>
class lazy_montgomery {
	// guarantees v is always in [0, mod * 2]
	static_assert(mod & 1, "modulus must be odd");
	static_assert(mod < 0x4000000000000000, "modulus must fit in 62 bits");
	using T1 = std::conditional_t<(mod < 0x40000000), uint32_t, uint64_t>;
	using T2 = std::conditional_t<(mod < 0x40000000), uint64_t, uint128_t>;
	using S1 = std::make_signed<T1>;
	using S2 = std::make_signed<T2>;
	template<typename S1>
	static constexpr S1 inv_normal(S1 n) {
		S1 w = 1, x = 0, y = m;
		while (n != 1) {
			S1 z = y / n;
			y -= n * z;
			x -= w * z;
			std::swap(y, n);
			std::swap(w, x);
		}
		return w < 0 ? w + m : w;
	}
	static const T1 m = mod;
	static const T1 m2 = m << 1;
	static const T1 r = (T1)-1 % m + 1;
	static const T1 r2 = (T2)-1 % m + 1;
	static const T1 r3 = ((T2)r2 << 32) % m;
	static const T1 nim = -inv_int(m);
	static constexpr T1 reduce(T2 a) {
		return (a + (T1)a * nim * (T2)m) >> sizeof(T1) * 8;
	}
	T1 v;
public:
	lazy_montgomery() : v(0) {}
	lazy_montgomery(T1 init) : v(reduce((T2)r2 * init)) {}
	T1 eval() {
		T1 ret = reduce(v);
		if (ret >= m2)
			ret -= m2;
		if (ret >= m)
			ret -= m;
		return ret;
	}
	lazy_montgomery& operator+=(lazy_montgomery rhs) {
		v += rhs.v;
		if (v >= m2)
			v -= m2;
		return *this;
	}
	lazy_montgomery& operator-=(lazy_montgomery rhs) {
		v -= rhs.v;
		if (v > m2)
			v += m2;
		return *this;
	}
	lazy_montgomery& operator*=(lazy_montgomery rhs) {
		v = reduce((T2)v * rhs.v);
		return *this;
	}
	lazy_montgomery& operator/=(lazy_montgomery rhs) {
		v = reduce((T2)v * reduce((T2)r3 * inv_normal(rhs.v)));
		return *this;
	}
	template<typename T>
	lazy_montgomery& operator^=(T rhs) {
		static_assert(std::is_integral_v<T>);
		lazy_montgomery b = *this;
		v = r;
		for (; rhs; rhs >>= 1) {
			if (rhs & 1)
				operator*=(b);
			b *= b;
		}
		return *this;
	}
	lazy_montgomery operator+(lazy_montgomery rhs) const {
		auto ret = *this;
		return ret += rhs;
	}
	lazy_montgomery operator-(lazy_montgomery rhs) const {
		auto ret = *this;
		return ret -= rhs;
	}
	lazy_montgomery operator*(lazy_montgomery rhs) const {
		auto ret = *this;
		return ret *= rhs;
	}
	lazy_montgomery operator/(lazy_montgomery rhs) const {
		auto ret = *this;
		return ret /= rhs;
	}
	template<typename T>
	lazy_montgomery operator^(T rhs) const {
		static_assert(std::is_integral_v<T>);
		lazy_montgomery b = *this;
		lazy_montgomery ret = 1;
		for (; rhs; rhs >>= 1) {
			if (rhs & 1)
				ret *= b;
			b *= b;
		}
		return ret;
	}
	lazy_montgomery operator-() const {
		v = m2 - v;
		return *this;
	}
	lazy_montgomery operator+() const {
		return *this;
	}
	lazy_montgomery& operator++() {
		v += r;
		if (v >= m)
			v -= m;
		return *this;
	}
	lazy_montgomery& operator--() {
		v -= r;
		if (v > m2)
			v += m;
		return *this;
	}
	lazy_montgomery operator++(int) {
		auto ret = *this;
		operator++();
		return ret;
	}
	lazy_montgomery operator--(int) {
		auto ret = *this;
		operator--();
		return ret;
	}
	bool operator==(lazy_montgomery rhs) const {
		return (v - rhs.v) % m == 0;
	}
	bool operator!=(lazy_montgomery rhs) const {
		return (v - rhs.v) % m != 0;
	}
	bool operator<(lazy_montgomery rhs) const {
		return v % m < rhs.v % m;
	}
	bool operator>(lazy_montgomery rhs) const {
		return v % m > rhs.v % m;
	}
	bool operator<=(lazy_montgomery rhs) const {
		return v % m <= rhs.v % m;
	}
	bool operator>=(lazy_montgomery rhs) const {
		return v % m >= rhs.v % m;
	}
};
using mint = lazy_montgomery<998244353>;
