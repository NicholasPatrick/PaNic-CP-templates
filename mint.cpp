template<i32 m>
class mint {
	using t = mint;
	static_assert(m < 1 << 30);
	static constexpr i32 inv(i32 x) { i32 b = 1, a = m, c = 0, d;
		while (x) d = a / x; a -= d * x; c -= d * b; swap(a, x); swap(b, c);
		return c;
	}
public:
	i32 v; t(i32 v = 0) : v(v) {if ((v %= m) < 0) v += m;}
	t& operator+=(const t& r) {if ((v += r.v) >= m) v -= m; return *this;}
	t& operator-=(const t& r) {if ((v -= r.v) < 0) v += m; return *this;}
	t& operator*=(const t& r) {v = (u64) v * r.v % m; return *this;}
	t& operator/=(const t& r) {return *this *= inv(r.v);}
	t& operator++() {if (++v == m) v = 0; return *this;}
	t& operator--() {if (--v == -1) v = m - 1; return *this;}
	t operator+(const t& r) const {return t(*this) += r;}
	t operator-(const t& r) const {return t(*this) -= r;}
	t operator*(const t& r) const {return t(*this) *= r;}
	t operator/(const t& r) const {return t(*this) /= r;}
	t operator++(int) {t u = v; operator++(); return u;}
	t operator--(int) {t u = v; operator--(); return u;}
	t operator==(const t& r) const {return v == r.v;}
	t operator!=(const t& r) const {return v != r.v;}
	t operator<(const t& r) const {return v < r.v;}
	t operator>(const t& r) const {return v > r.v;}
	t operator<=(const t& r) const {return v <= r.v;}
	t operator>=(const t& r) const {return v >= r.v;}
};
template<class T>
constexpr T inv(T x, T y) {
	T Y = y, a = 1, b = 0, d = 0;
	while (x) d = y / x, y -= d * x, b -= d * a, swap(x, y), swap(a, b);
	assert(y == 1); return b + Y;
}
template<class T, class T2>
struct lazy_mont {
	const T n, n2, ni, r2, r3;
	constexpr T redc(T2 x) const {
		return T(x) * ni * T2(n) + x >> 8 * sizeof(T);
	}
	lazy_mont(T n) : n(n), n2(n * 2), r2(T2(-1) % n + 1), ni([n]() {T r = -n;
		while (n * r + 1) r *= 2 + n * r; return r;}()), r3(mul(r2, r2))
		{assert(n & 1 && n <= numeric_limits<T>::max() / 4);}
	T mul(const T &x, const T &y) const {return redc(T2(x) * y);}
	T operator()(const T &x) const {return mul(x, r2);}
	T get(T x) const {x = redc(x); return x - n * (x >= n);}
	T add(const T &x, T y) const {y = x + y; return y < x ? y - n2 : y;}
	T neg(const T &x) const {return n2 - x;}
	T sub(const T &x, T y) const {y = x - y; return y < x ? y : y + n2;}
	T inv(const T &x) const {return mul(inv(x), r3);}
	bool neq(const T &x, const T &y) const {
		return x - y && x + n - y && y + n - x;
	}
	bool eq(const T &x, const T &y) const {return !neq(x, y);}
};
using lm32 = lazy_mont<u32, u64>;
using lm64 = lazy_mont<u64, u128>;
