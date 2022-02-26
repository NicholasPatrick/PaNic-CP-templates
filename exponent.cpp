template <class v_t, class e_t>
v_t mulexp(v_t a, v_t b, e_t e) {
	for (; e; e >>= 1, b *= b) if (e & 1) a *= b; return a;
}
template <class v_t, class e_t>
v_t expmul(v_t b, e_t e, v_t a) {
	for (; e; e >>= 1, b *= b) if (e & 1) a = b * a; return a;
}
u32 modexp(u32 b, auto e, u32 m) {
	u32 r = 1;
	for (; e; e >>= 1, b = (u64) b * b % m) if (e & 1) r = (u64) r * b % m;
	return r;
}