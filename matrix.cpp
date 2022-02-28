/*
replace add_id() with + identity
for tropic, it's T::zero()
for countmin/max, it's T()
for reals and mint, it's 0
replace mul_id() with * identity
for tropic, it's T::one()
for reals and mint, it's 1
for countmin/max, remove the constructor
*/
template <class T>
class matrix : public vector<T> {
	using p_t = vector<T>; u32 n, m;
	class matrix_row {
		class p_t::iterator from;
		friend matrix_row matrix::operator[](u32 x);
		matrix_row(class p_t::iterator f) : from(f) {}
	public:
		T& operator[](u32 y) const {return *(from + y);}
	};
public:
	matrix() : n(0), m(0) {} matrix(u32 n, u32 m) : n(n), m(m), p_t(n * m) {}
	matrix(u32 n, u32 m, T init) : n(n), m(m), p_t(n * m, init) {}
	u32 r() const {return n;} u32 c() const {return m;}
	T& at(u32 x, u32 y) {return p_t::at(x * m + y);}
	matrix_row operator[](u32 x) {return matrix_row(p_t::begin() + x * m);}
	matrix(u32 n) : n(n), m(n), p_t(n * m, mul_id()) {
		for (u32 i = 0; i < n * n; i += n + 1) o(i) = add_id();
	}
private:
	T& o(u32 i) {return p_t::operator[](i);}
	static matrix mult(const matrix& lhs, const matrix& rhs) {
		assert(lhs.m == rhs.n);
		u32 a = lhs.n, b = lhs.m, c = rhs.m; matrix ret(a, c, add_id());
		for (u32 i = a; i--;) for (u32 j = b; j--;) for (u32 k = c; k--;)
			ret.o(i * c + k) += lhs.o(i * b + j) * rhs.o(j * c + k);
		return ret;
	}
	static matrix transp(const matrix& A) {
		matrix B(A.m, A.n);
		for (u32 i = A.n; i--;) for (u32 j = A.m; j--;)
			B.o(j * B.m + i) = A.o(i * A.m + j);
		return B;
	}
public:
	matrix& operator+=(const matrix& rhs) {
		assert(n == rhs.n and m == rhs.m);
		for (u32 i = 0; i < n; ++i) for (u32 j = 0; j < m; ++j)
			o(i * m + j) += rhs.o(i * m + j);
		return *this;
	}
	matrix& operator-=(const matrix& rhs) {
		assert(n == rhs.n and m == rhs.m);
		for (u32 i = 0; i < n; ++i) for (u32 j = 0; j < m; ++j)
			o(i * m + j) -= rhs.o(i * m + j);
		return *this;
	}
	matrix& dot_eq(const matrix& rhs) {
		assert(n == rhs.n and m == rhs.m);
		for (u32 i = 0; i < n; ++i) for (u32 j = 0; j < m; ++j)
			o(i * m + j) *= rhs.o(i * m + j);
		return *this;
	}
	matrix& operator*=(const matrix& rhs) {return *this = mult(*this, rhs);}
	matrix& transpose_eq() {return *this = transp(*this);}
	matrix operator+(const matrix& rhs) const {return (matrix)*this += rhs;}
	matrix operator-(const matrix& rhs) const {return (matrix)*this -= rhs;}
	matrix dot(const matrix& rhs) const {return ((matrix)*this).doteq(rhs);}
	matrix operator*(const matrix& rhs) const {return mult(*this, rhs);}
	matrix transpose() {return transp(*this);}
};