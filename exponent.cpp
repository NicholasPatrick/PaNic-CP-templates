template<class v_t, class e_t>
v_t mulexp(v_t a, v_t b, e_t e) {
	for (; e; e >>= 1, b *= b) if (e & 1) a *= b; return a;
}
template<class v_t, class e_t>
v_t expmul(v_t b, e_t e, v_t a) {
	for (; e; e >>= 1, b *= b) if (e & 1) a = b * a; return a;
}
template<class e_t>
u32 modexp(u32 b, e_t e, u32 m) {
	u32 r = 1;
	for (; e; e >>= 1, b = (u64) b * b % m) if (e & 1) r = (u64) r * b % m;
	return r;
}
// template<class e_t>
// u32 modexp(u32 b, e_t e) {return expmul<mint<MOD>>(b, e, 1);}
template<class n_t>
u32 geo_series(u32 a, u32 r, n_t n, u32 m) {
	u32 t = 0;
	while (n) {
		if (n & 1) t = (t + a) % m, a = u64(a) * r % m;
		a = u64(a + 1) * a % m; r = u64(r) * r % m; n >>= 1;
	}
	return t;
}
