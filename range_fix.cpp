template<class T>
auto associative_all_range_fixed_size(const vector<T>& a, u32 k, auto f) {
	if (k == 1) return a; u32 n = a.size(); vector<T> p(n), s(n);
	for (u32 i = 0; i < n; i += k - 1) { u32 j = min(i + k - 2, n - 1);
		p[i] = a[i]; for (u32 k = i; k++ < j;) p[k] = f(p[k - 1], a[k]);
		s[j] = a[j]; for (u32 k = j; k-- > i;) s[k] = f(a[k], s[k + 1]);
	} vector<T> r(n - k + 1);
	for (u32 i = 0; i + k <= n; ++i) r[i] = f(s[i], p[i + k - 1]); return r;
};
