template<class v_t, class e_t>
v_t mulexp(v_t a, v_t b, e_t e) {
	for (; e; e >>= 1, b *= b) if (e & 1) a *= b; return a;
}
template<class v_t, class e_t>
v_t expmul(v_t b, e_t e, v_t a) {
	for (; e; e >>= 1, b *= b) if (e & 1) a = b * a; return a;
}
template<class T, class T2, class e_t>
T modexp(T b, e_t e, const lazy_mont<T, T2>& lm) {
	T r = lm(1);
	for (; e; e >>= 1, b = lm.sq(b)) if (e & 1) r = lm.mul(r, b);
	return r;
}
template<class e_t>
u32 modexp(u32 b, e_t e, u32 m) {lm32 lm(m); return modexp(lm(b), e, lm);}
template<class e_t>
u64 modexp(u64 b, e_t e, u64 m) {lm64 lm(m); return modexp(lm(b), e, lm);}
template<class T, class T2, class n_t>
T geo_series(T a, T r, n_t n, const lazy_mont<T, T2>& lm) {
	T t = 0;
	while (n) {
		if (n & 1) t = lm.add(t, a), a = lm.mul(a, r);
		a = lm.mul(a, a + 1); r = lm.sq(r); n >>= 1;
	}
	return t;
}
template<class n_t>
u32 geo_series(u32 a, u32 r, n_t n, u32 m) {
	lm32 lm(m); return geo_series(lm(a), lm(r), n, lm);
}
template<class n_t>
u64 geo_series(u64 a, u64 r, n_t n, u64 m) {
	lm64 lm(m); return geo_series(lm(a), lm(r), n, lm);
}
