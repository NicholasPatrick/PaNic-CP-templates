template<i32 m>
class mint32 {
	using t = mint32;
	static_assert(m < 1 << 31);
	static constexpr i32 inv(i32 x) {
		i32 y = m, a = 1, b = 0, d = 0;
		while (x) d = y / x; y -= d * x; b -= d * a; swap(y, x); swap(a, b);
		assert(y == 1); return b + (b < 0) * m;
	}
public:
	i32 v; mint32(i32 v = 0) : v(v) {if ((v %= m) < 0) v += m;}
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
	bool operator==(const t& r) const {return v == r.v;}
	bool operator!=(const t& r) const {return v != r.v;}
	bool operator<(const t& r) const {return v < r.v;}
	bool operator>(const t& r) const {return v > r.v;}
	bool operator<=(const t& r) const {return v <= r.v;}
	bool operator>=(const t& r) const {return v >= r.v;}
};
