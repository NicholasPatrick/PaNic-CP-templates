const fe dtr = 0.017453292519943295l;
const fe rtd = 57.29577951308232l;
template<class T = i32>
struct p3 {
	using t = p3<T>;
	T x, y, z; p3() {} p3(T x, T y, T z) : x(x), y(y), z(z) {}
	t& operator+=(const t &r) {x += r.x; y += r.y; z += r.z; return *this;}
	t& operator-=(const t &r) {x -= r.x; y -= r.y; z -= r.z; return *this;}
	t operator+(const t& r) const {return t(*this) += r;}
	t operator-(const t& r) const {return t(*this) -= r;}
};
template<class T2 = i64, class T>
T2 sq(T x) {return T2(x) * x;}
template<class T2 = i64, class T>
T2 length(p3<T> a) {return sq<T2>(a.x) + sq<T2>(a.y) + sq<T2>(a.z);}
template<class T2 = i64, class T>
T2 dist(p3<T> a, p3<T> b) {return length<T2>(b - a);}
template<class T2 = i64, class T>
T2 dot(p3<T> a, p3<T> b) {
	return T2(a.x) * b.x + T2(a.y) * b.y + T2(a.z) * b.z;
}
template<class T2 = i64, class T>
p3<T2> cross(p3<T> a, p3<T> b) {
	return p3<T2>(T2(a.x) * b.y - T2(a.y) * b.x,
		T2(a.y) * b.z - T2(a.z) * b.y,
		T2(a.z) * b.x - T2(a.x) * b.z);
}
template<class T2 = i64, class T>
p3<T2> cross3(p3<T> a, p3<T> b, p3<T> c) {return cross<T2>(b - a, c - a);}
template<class T2 = i64, class T>
T2 tetvol(p3<T> a, p3<T> b, p3<T> c, p3<T> d) {
	return dot<T2>(cross3<T2>(a, b, c), d);
}
