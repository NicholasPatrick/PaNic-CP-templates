template<class T, class T2>
struct lazy_mont {
	static_assert(is_unsigned_v<T> && is_unsigned_v<T2>);
	static_assert(sizeof(T2) == sizeof(T) * 2);
	using iT = make_signed_t<T>;
	const T n, n2, ni, r2, r3;
	constexpr T redc(T2 x) const {
		return T(x) * ni * T2(n) + x >> 8 * sizeof(T);
	}
	T st_inv(iT x) {
		if (x >= n) x -= n;
		iT y = n, a = 1, b = 0, d = 0;
		while (x) d = y / x, y -= d * x, b -= d * a, swap(x, y), swap(a, b);
		assert(y == 1); return b + n;
	}
	constexpr lazy_mont(T n) : n(n), n2(n * 2), r2(T2(-1) % n + 1), ni([n]() {T r = -n;
		while (n * r + 1) r *= 2 + n * r; return r;}()), r3(mul(r2, r2))
		{assert(n & 1 && n <= numeric_limits<T>::max() / 4);}
	T mul(const T &x, const T &y) const {return redc(T2(x) * y);}
	T sq(const T &x) const {return redc(T2(x) * x);}
	T operator()(const T &x) const {return mul(x, r2);}
	T get(T x) const {x = redc(x); return x - n * (x >= n);}
	T add(const T &x, T y) const {y = x + y; return y < n2 ? y : y - n2;}
	T neg(const T &x) const {return n2 - x;} // doesn't guarantee [0, 2n)
	T sub(const T &x, T y) const {y = x - y; return y <= x ? y : y + n2;}
	T inv(const T &x) const {return mul(st_inv(x), r3);}
	T div(const T &x, const T &y) const {return mul(x, inv(y));}
	bool neq(const T &x, const T &y) const {
		return x - y && x + n - y && y + n - x;
	}
	bool eq(const T &x, const T &y) const {return !neq(x, y);}
	bool zero(const T &x) const {return x == 0 || x == n;}
	bool nonzero(const T &x) const {return x && x - n;}
};
using lm32 = lazy_mont<u32, u64>;
using lm64 = lazy_mont<u64, u128>;
