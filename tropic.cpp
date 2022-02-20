template <class T, T z = numeric_limits<T>::max() / 2>
struct tropicmin {
	T v;
	tropicmin(T v = 0) : v(v) {}
    static const tropicmin zero() {return z;}
    static const tropicmin one() {return 0;}
	tropicmin operator+(tropicmin rhs) const {return min(v, rhs.v);}
	tropicmin operator*(tropicmin rhs) const {return v + rhs.v;}
	tropicmin& operator+=(tropicmin rhs) {v = min(v, rhs.v); return *this;}
	tropicmin& operator*=(tropicmin rhs) {v += rhs.v;return *this;}
	bool operator<(tropicmin rhs) const {return v < rhs.v;}
	bool operator<=(tropicmin rhs) const {return v <= rhs.v;}
	bool operator>(tropicmin rhs) const {return v > rhs.v;}
	bool operator>=(tropicmin rhs) const {return v >= rhs.v;}
	bool operator!=(tropicmin rhs) const {return v != rhs.v;}
	bool operator==(tropicmin rhs) const {return v == rhs.v;}
};
using tmin32 = tropicmin<i32>;
using tmin64 = tropicmin<i64>;
template <class T, T z = numeric_limits<T>::min() / 2>
struct tropicmax {
	T v;
	tropicmax(T v = 0) : v(v) {}
    static const tropicmax zero() {return z;}
    static const tropicmax one() {return 0;}
	tropicmax operator+(tropicmax rhs) const {return max(v, rhs.v);}
	tropicmax operator*(tropicmax rhs) const {return v + rhs.v;}
	tropicmax& operator+=(tropicmax rhs) {v = max(v, rhs.v); return *this;}
	tropicmax& operator*=(tropicmax rhs) {v += rhs.v;return *this;}
	bool operator<(tropicmax rhs) const {return v < rhs.v;}
	bool operator<=(tropicmax rhs) const {return v <= rhs.v;}
	bool operator>(tropicmax rhs) const {return v > rhs.v;}
	bool operator>=(tropicmax rhs) const {return v >= rhs.v;}
	bool operator!=(tropicmax rhs) const {return v != rhs.v;}
	bool operator==(tropicmax rhs) const {return v == rhs.v;}
};
using tmax32 = tropicmax<i32>;
using tmax64 = tropicmax<i64>;
