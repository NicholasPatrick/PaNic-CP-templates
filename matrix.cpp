#include <cstdio>
#include <queue>
#include <cassert>
#include <cstdint>
#include <type_traits>

template <typename T>
struct matrix : std::vector<T> {
	using pc = std::vector<T>; // parent class
	struct matrix_row {
		typename pc::iterator from;
	public:
		matrix_row(typename pc::iterator f) : from(f) {}
		T& operator[](uint32_t y) {
			return *(from + y);
		}
	};
	uint32_t n, m;
public:
	matrix() : n(0), m(0) {}
	matrix(uint32_t n, uint32_t m) : n(n), m(m), pc(n * m){}
	uint32_t r() const {return n;}
	uint32_t c() const {return m;}
	T& at(uint32_t x, uint32_t y) {
		return pc::at(x * m + y);
	}
	matrix_row operator[](uint32_t x) {
		return matrix_row(pc::begin() + x * m);
	}
	matrix operator+(matrix rhs) const {
		assert(n == rhs.n and m == rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++)
			rhs.at(i, j) = at(i, j) + rhs.at(i, j);
		return rhs;
	}
	matrix operator-(matrix rhs) const {
		assert(n == rhs.n and m == rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++)
			rhs.at(i, j) = at(i, j) - rhs.at(i, j);
		return rhs;
	}
	matrix dot(matrix rhs) const {
		assert(n == rhs.n and m == rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++)
			rhs.at(i, j) = at(i, j) * rhs.at(i, j);
		return rhs;
	}
	matrix operator*(const matrix& rhs) const {
		assert(m == rhs.n);
		matrix ret(n, rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++){
			for (uint32_t k = 0; k < rhs.m; k++) {
				ret.pc::operator[](i * rhs.m + k) = ret.pc::operator[](i * rhs.m + k) +
					pc::operator[](i * m + j) * rhs.pc::operator[](j * rhs.m + k)
				;
			}
		}
		return ret;
	}
	matrix& operator+=(const matrix& rhs) {
		assert(n == rhs.n and m == rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++)
			pc::operator[](i * m + j) = pc::operator[](i * m + j) +
			rhs.pc::operator[](i * m + j);
		return *this;
	}
	matrix& operator-=(const matrix& rhs) {
		assert(n == rhs.n and m == rhs.m);
		for (uint32_t i = 0; i < n; i++) for (uint32_t j = 0; j < m; j++)
			pc::operator[](i * m + j) = pc::operator[](i * m + j) -
			rhs.pc::operator[](i * m + j);
		return *this;
	}
	matrix& operator*=(const matrix& rhs) {
		return *this = operator*(rhs);
	}
	T determinant() const {
		assert(n == m);
		for (uint32_t i = 0; i < n; i++) {
			uint32_t ini = i * n + i;
			if (pc::operator[](ini) != 1) {
				if (pc::operator[](ini) == 0) {
					for (uint32_t j = ini; j < n * n; j += m) {
						if (pc::operator[](j) != 0) {
							std::swap_ranges(pc::operator[].begin() + j,
								pc::operator[].begin() + j + n - i, pc::operator[].begin() + ini);
							break;
						}
					}
				}
				if (pc::operator[](ini) == 0)
					return 0;
				if constexpr (std::is_fundamental_v<T>) {
					pc::operator[](ini) = 1 / pc::operator[](ini);
				} else {
					pc::operator[](ini) = pc::operator[](ini).inv();
				}
				for (uint32_t j = ini; j < ini + n - i; j++)
					pc::operator[](j) *= pc::operator[](ini);
				pc::operator[](ini) = 1;
			}
		}
	}
};
template <int32_t mod>
struct mint {
	int32_t v;
	mint(int32_t v = 0) : v(v) {}
	mint operator+(mint rhs) const {
		int32_t d = v + rhs.v;
		return d < mod ? d : d - mod;
	}
	mint operator-(mint rhs) const {
		int32_t d = v - rhs.v;
		return d < 0 ? d + mod : d;
	}
	mint operator*(mint rhs) const {
		return (int64_t)v * rhs.v % mod;
	}
	mint inv() const {
		int32_t a = 1, b = 0, c = v, d = mod;
		while (c != 1) {
			int32_t e = d / c;
			d -= c * e;
			b -= a * e;
			e = a; a = b; b = e;
			e = c; c = d; d = e;
		}
		return a < 0 ? a + mod : a;
	}
	mint operator/(mint rhs) const {
		return operator*(rhs.inv());
	}
	mint abs() const {
		return *this;
	}
};
