template <class v_t, class c_t = u32, v_t z = numeric_limits<v_t>::max()>
struct count_min {
	v_t v; c_t c;
	count_min() : v(z), c(0) {}
	count_min(v_t v, c_t c = 1) : v(v), c(c) {}
	static const count_min zero() {return count_min();}
	static const count_min one() {return 0;}
	count_min operator+(count_min rhs) const {
		if (v < rhs.v) return *this;
		if (v > rhs.v) return rhs;
		return count_min(min(v, rhs.v), c + rhs.c);
	}
	count_min& operator+=(count_min rhs) {v = min(v, rhs.v); return *this;}
	bool operator<(count_min rhs) const {return v < rhs.v;}
	bool operator<=(count_min rhs) const {return v <= rhs.v;}
	bool operator>(count_min rhs) const {return v > rhs.v;}
	bool operator>=(count_min rhs) const {return v >= rhs.v;}
	bool operator!=(count_min rhs) const {return v != rhs.v;}
	bool operator==(count_min rhs) const {return v == rhs.v;}
};
using cmini32 = count_min<i32>;
using cminu32 = count_min<u32>;
using cmini64 = count_min<i64>;
using cminu64 = count_min<u64>;
template <class v_t, class c_t = u32, v_t z = numeric_limits<v_t>::min()>
struct count_max {
	v_t v; c_t c;
	count_max() : v(z), c(0) {}
	count_max(v_t v, c_t c = 1) : v(v), c(c) {}
	static const count_max zero() {return count_max();}
	static const count_max one() {return 0;}
	count_max operator+(count_max rhs) const {
		if (v < rhs.v) return *this;
		if (v > rhs.v) return rhs;
		return count_max(max(v, rhs.v), c + rhs.c);
	}
	count_max& operator+=(count_max rhs) {v = max(v, rhs.v); return *this;}
	bool operator<(count_max rhs) const {return v < rhs.v;}
	bool operator<=(count_max rhs) const {return v <= rhs.v;}
	bool operator>(count_max rhs) const {return v > rhs.v;}
	bool operator>=(count_max rhs) const {return v >= rhs.v;}
	bool operator!=(count_max rhs) const {return v != rhs.v;}
	bool operator==(count_max rhs) const {return v == rhs.v;}
};
using cmaxi32 = count_max<i32>;
using cmaxu32 = count_max<u32>;
using cmaxi64 = count_max<i64>;
using cmaxu64 = count_max<u64>;