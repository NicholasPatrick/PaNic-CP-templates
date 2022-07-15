template<class T = i32>
struct p2 {
	using t = p2<T>;
	T x, y; p2() {} p2(T x, T y) : x(x), y(y) {}
	t& operator+=(const t &r) {x += r.x; y += r.y; return *this;}
	t& operator-=(const t &r) {x -= r.x; y -= r.y; return *this;}
	t operator+(const t& r) const {return t(*this) += r;}
	t operator-(const t& r) const {return t(*this) -= r;}
	bool operator==(const t& r) const {return x == r.x && y == r.y;}
	bool operator!=(const t& r) const {return x != r.x || y != r.y;}
	bool operator<(const t& r) const {return x == r.x ? y < r.y : x < r.x;}
	bool operator>(const t& r) const {return x == r.x ? y > r.y : x > r.x;}
	bool operator<=(const t& r) const {return x == r.x ? y <= r.y : x <= r.x;}
	bool operator>=(const t& r) const {return x == r.x ? y >= r.y : x >= r.x;}
};
template<class T2 = i64, class T>
T2 sq(T x) {return T2(x) * x;}
template<class T2 = i64, class T>
T2 length(p2<T> a) {return sq<T2>(a.x) + sq<T2>(a.y);}
template<class T2 = i64, class T>
T2 dist(p2<T> a, p2<T> b) {return length<T2>(b - a);}
template<class T2 = i64, class T>
T2 dot(p2<T> a, p2<T> b) {return T2(a.x) * b.x + T2(a.y) * b.y;}
template<class T2 = i64, class T>
T2 cross(p2<T> a, p2<T> b) {return T2(a.x) * b.y - T2(a.y) * b.x;}
template<class T2 = i64, class T>
T2 cross3(p2<T> a, p2<T> b, p2<T> c) {return cross<T2>(b - a, c - a);}
template<class T2 = i64, class T>
T2 area(vector<p2<T>> s) {
	u32 n = s.size(); T2 a = 0;
	for (u32 i = 0; i < n; ++i) a += cross<T2>(s[i], s[mod1(j + 1, n)]);
	return a;
}
template<class T2 = i64, class T>
vector<p2<T>> convex_hull(vector<p2<T>> s) {
	sort(bend(s));
	vector<p2<T>> r;
	for (auto &i : s) {
		while (r.size() > 1 && cross3<T2>(r.end()[-2], r.back(), i) <= 0)
			r.pop_back();
		r.push_back(i);
	}
	u32 lim = r.size();
	for (auto i = next(s.rbegin()); i != s.rend(); ++i) {
		while (r.size() > lim && cross3<T2>(r.end()[-2], r.back(), *i) <= 0)
			r.pop_back();
		r.push_back(*i);
	}
	r.pop_back();
	return r;
}
template<class T2 = i64, class T>
bool pointInSegment(p2<T> a, p2<T> b, p2<T> c) {
	if (a.x > b.x && c.x > b.x) return 0;
	if (a.x < b.x && c.x < b.x) return 0;
	if (a.y > b.y && c.y > b.y) return 0;
	if (a.y < b.y && c.y < b.y) return 0;
	return !cross3<T2>(a, b, c);
}
template<class T2 = i64, class T>
auto pointInPolygon(std::vector<p2<T>> s, p2<T> a) {
	u32 n = s.size(); bool parity = 0;
	for (u32 i = 0; i < n; ++i) {
		u32 j = i ? i - 1 : n - 1;
		if (pointInSegment<T2>(s[j], a, s[i])) return 0;
		if (s[j].y <= a.y ^ s[i].y <= a.y)
			parity ^= s[j].y < s[i].y ^
				T2(a.x - s[i].x) * (s[j].y - s[i].y) <
				T2(s[j].x - s[i].x) * (a.y - s[i].y);
	}
	return parity ? 1 : -1;
}
template<class T2 = i64, class T>
array<u32, 4> largest_quad(const vector<p2<T>> &s) {
	using u324 = array<u32, 4>;
	u32 n = s.size();
	if (n < 4) {return {};}
	u324 best_conf; T2 best_area = 0;
	auto calc_area = [&](const u324 &test) {
		T2 r = cross3<T2>(s[test[0]], s[test[1]], s[test[2]]) +
			cross3<T2>(s[test[0]], s[test[2]], s[test[3]]);
		if (r > best_area) best_area = r, best_conf = test; return r;
	};
	u324 test{0, 1, 2, 3};
	for (; test[2] < n; ++test[2]) {
		while (test[1] + 1 < test[2] &&
			cross<T2>(s[test[1] + 1] - s[test[1]],
			s[test[2]] - s[test[0]]) >= 0)
			++test[1];
		while (test[3] + 1 < n &&
			cross<T2>(s[test[3] + 1] - s[test[3]],
			s[test[2]] - s[test[0]]) <= 0)
			++test[3];
		calc_area(test);
	}
	vector<u32> candy;
	candy.reserve(n); u32 m;
	u324 local_ind, local_conf, local_test, ret; T2 local_area;
	auto root = [&](const u324 &l, const u324 &r, u32 fix, u32 val) {
		candy.clear(); candy.push_back(val);
		for (u8 i = fix + 1 & 3; i != fix; i = i + 1 & 3)
			for (u32 j = l[i]; j <= r[i]; ++j) if (candy.back() != j)
				candy.push_back(j);
		m = candy.size(); local_ind = {0, 1, 2, 3}; local_area = 0;
		auto fix0 = s[candy[local_ind[0]]];
		for (; local_ind[2] < m; ++local_ind[2]) {
			auto fix20 = s[candy[local_ind[2]]] - fix0;
			while (local_ind[1] + 1 < local_ind[2] &&
				cross<T2>(s[candy[local_ind[1] + 1]] - s[candy[local_ind[1]]],
				fix20) >= 0)
				++local_ind[1];
			while (local_ind[3] + 1 < m &&
				cross<T2>(s[candy[local_ind[3] + 1]] - s[candy[local_ind[3]]],
				fix20) <= 0)
				++local_ind[3];
			for (u8 i = 4; i--;) local_test[i] = candy[local_ind[i]];
			T2 area = calc_area(local_test);
			if (area > local_area) {
				local_area = area;
				local_conf = local_test;
			}
		}
		for (u8 i = 4; i--;) ret[i + fix & 3] = local_conf[i];
		return ret;
	};
	auto solve = [&](auto self, u324 &l, u324 &r) -> void {
		for (u8 i = 4; i--;) if (l[i] == r[i]) {root(l, r, i, l[i]); return;}
		for (u8 i = 4; i--;) if (l[i] + 1 == r[i]) {
			root(l, r, i, l[i]); root(l, r, i, r[i]); return;
		}
		u32 ms = 0; for (u8 i = 4; i--;) cmax(ms, r[i] - l[i]);
		for (u8 i = 4; i--;) {
			if (r[i] - l[i] == ms) {
				u32 mid = l[i] + r[i] >> 1;
				u324 splitter = root(l, r, i, mid);
				u8 status = 0;
				for (u8 j = i + 1 & 3; j != i; j = j + 1 & 3) {
					if (splitter[j] < l[j])
						status |= mid < splitter[j] ^ mid < l[j] ? 2 : 1;
					if (splitter[j] > r[j])
						status |= mid < splitter[j] ^ mid < r[j] ? 1 : 2;
				}
				if (status == 3) return;
				if (status == 0) {
					--splitter[i];
					self(self, l, splitter);
					splitter[i] += 2;
					self(self, splitter, r);
					return;
				}
				for (u8 j = 4; j--;) if (splitter[j] < mid) splitter[j] += n;
				for (u8 j = i; j--;) l[j] += n, r[j] += n;
				if (status == 1) {
					cmax(l[i], splitter[i] + 1);
					cmin(r[i], splitter[i + 1 & 3]);
					cmax(l[i + 1 & 3], splitter[i + 1 & 3]);
					cmin(r[i + 1 & 3], splitter[i + 2 & 3]);
					cmax(l[i + 2 & 3], splitter[i + 2 & 3]);
					cmin(r[i + 2 & 3], splitter[i + 3 & 3]);
					cmax(l[i + 3 & 3], splitter[i + 3 & 3]);
					cmin(r[i + 3 & 3], splitter[i] - 1 + n);
				} else if (status == 2) {
					cmax(l[i], splitter[i + 3 & 3] - n);
					cmin(r[i], splitter[i] - 1);
					cmax(l[i + 1 & 3], splitter[i] + 1);
					cmin(r[i + 1 & 3], splitter[i + 1 & 3]);
					cmax(l[i + 2 & 3], splitter[i + 1 & 3]);
					cmin(r[i + 2 & 3], splitter[i + 2 & 3]);
					cmax(l[i + 3 & 3], splitter[i + 2 & 3]);
					cmin(r[i + 3 & 3], splitter[i + 3 & 3]);
				}
				for (u8 j = 4; j--;) if (l[j] > r[j]) return;
				for (u8 j = i; j--;) l[j] -= n, r[j] -= n;
				return self(self, l, r);
			}
		}
	};
	test = best_conf;
	u324 l{1, test[1], test[2], test[3]}, r{test[1], test[2], test[3], n - 1};
	solve(solve, l, r);
	return best_conf;
}
template<class T2 = i64, class T>
pair<u32, u32> closest(const vector<p2<T>> &s) {
	u32 n = s.size(); vector<u32> ind(n); iota(bend(ind), 0);
	sort(bend(ind), [&](u32 a, u32 b) {return s[a].x < s[b].x;});
	T2 d = numeric_limits<T2>::max(); pair<u32, u32> ret;
	vector<u32> indl, indr; indl.reserve(n >> 1); indr.reserve(n + 1 >> 1);
	auto solve = [&](auto self, u32 l, u32 r) {
		if (r - l <= 1) return;
		u32 mid = l + r >> 1, lx = s[ind[mid - 1]].x, rx = s[ind[mid]].x;
		self(self, l, mid); self(self, mid, r);
		indl.clear(); for (u32 i = l; i < mid; ++i)
			if (sq<T2>(s[ind[i]].x - rx) < d) indl.push_back(ind[i]);
		indr.clear(); for (u32 i = mid; i < r; ++i)
			if (sq<T2>(s[ind[i]].x - lx) < d) indr.push_back(ind[i]);
		u32 j = 0;
		for (u32 i : indl) {
			const auto &si = s[i]; T iy = si.y;
			while (j < indr.size() && s[indr[j]].y < iy &&
				sq<T2>(s[indr[j]].y - iy) >= d)
				++j;
			for (u32 k = j; k < indr.size() && sq<T2>(s[indr[k]].y - iy) < d;
				++k) {
				T2 rec = dist<T2>(si, s[indr[k]]);
				if (d > rec) d = rec, ret = {i, indr[k]};
			}
		}
		inplace_merge(ind.begin() + l, ind.begin() + mid, ind.begin() + r,
			[&](u32 a, u32 b) {return s[a].y < s[b].y;});
	};
	solve(solve, 0, n);
	return ret;
}
