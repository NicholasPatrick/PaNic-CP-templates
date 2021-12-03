//tropic.cpp
template <typename T>
struct tropicmin {
	T a;
	tropicmin() {}
	tropicmin(T a) : a(a) {}
	tropicmin operator+(tropicmin rhs) const {
		return std::min(a, rhs.a);
	}
	tropicmin operator*(tropicmin rhs) const {
		return a + rhs.a;
	}
	tropicmin operator+=(tropicmin rhs) {
		return a = std::min(a, rhs.a);
	}
	tropicmin operator*=(tropicmin rhs) {
		return a += rhs.a;
	}
	bool operator<(tropicmin rhs) const {
		return a < rhs.a;
	}
	bool operator<=(tropicmin rhs) const {
		return a <= rhs.a;
	}
	bool operator>(tropicmin rhs) const {
		return a > rhs.a;
	}
	bool operator>=(tropicmin rhs) const {
		return a >= rhs.a;
	}
	bool operator!=(tropicmin rhs) const {
		return a != rhs.a;
	}
	bool operator==(tropicmin rhs) const {
		return a == rhs.a;
	}
};
template <typename T>
struct tropicmax {
	T a;
	tropicmax() {}
	tropicmax(T a) : a(a) {}
	tropicmax operator+(tropicmax rhs) const {
		return std::max(a, rhs.a);
	}
	tropicmax operator*(tropicmax rhs) const {
		return a + rhs.a;
	}
	tropicmax operator+=(tropicmax rhs) {
		return a = std::max(a, rhs.a);
	}
	tropicmax operator*=(tropicmax rhs) {
		return a += rhs.a;
	}
	bool operator<(tropicmax rhs) const {
		return a < rhs.a;
	}
	bool operator<=(tropicmax rhs) const {
		return a <= rhs.a;
	}
	bool operator>(tropicmax rhs) const {
		return a > rhs.a;
	}
	bool operator>=(tropicmax rhs) const {
		return a >= rhs.a;
	}
	bool operator!=(tropicmax rhs) const {
		return a != rhs.a;
	}
	bool operator==(tropicmax rhs) const {
		return a == rhs.a;
	}
};