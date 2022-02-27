template<i32 m>
class mint {
	static_assert(m < 1 << 30); i32 v;
	static constexpr i32 inv(i32 x) { i32 b = 1, a = m, c = 0, d;
		while (x) d = a / x; a -= d * x; c -= d * b; swap(a, x); swap(b, c);
		return c;
	}
public:
	mint(i32 v = 0) : v(v) {if ((v %= m) < 0) v += m;}
	mint& operator+=(const mint& r) {if ((v += r.v) >= m) v -= m; return *this;}
	mint& operator-=(const mint& r) {if ((v -= r.v) < 0) v += m; return *this;}
	mint& operator*=(const mint& r) {v = (u64) v * r.v % m; return *this;}
	mint& operator/=(const mint& r) {return *this *= inv(r.v);}
	mint& operator++() {if (++v == m) v = 0; return *this;}
	mint& operator--() {if (--v == -1) v = m - 1; return *this;}
	mint operator+(const mint& r) const {return mint(*rhs) += r;}
	mint operator-(const mint& r) const {return mint(*rhs) -= r;}
	mint operator*(const mint& r) const {return mint(*rhs) *= r;}
	mint operator/(const mint& r) const {return mint(*rhs) /= r;}
	mint operator++(int) {return v++;}
	mint operator--(int) {return v--;}
	mint operator==(const mint& rhs) const {return v == rhs.v;}
	mint operator!=(const mint& rhs) const {return v != rhs.v;}
	mint operator<(const mint& rhs) const {return v < rhs.v;}
	mint operator>(const mint& rhs) const {return v > rhs.v;}
	mint operator<=(const mint& rhs) const {return v <= rhs.v;}
	mint operator>=(const mint& rhs) const {return v >= rhs.v;}
};