bool mr32(u32 n, u32 a) {
	if (!(a %= n)) return 1;
	u8 r = __builtin_ctz(n - 1); u32 d = n >> r, p = 1;
	for (; d; d >>= 1, a = u64(a) * a % n) {if (d & 1) p = u64(p) * a % n;}
	if (p == 1) return 1;
	while (p != n - 1 && --r) {p = u64(p) * p % n;}
	return p == n - 1;
}
bool mr64(u64 n, u64 a) {
	if (!(a %= n)) return 1;
	u8 r = __builtin_ctzll(n - 1); u64 d = n >> r, p = 1;
	for (; d; d >>= 1, a = u128(a) * a % n) {if (d & 1) p = u128(p) * a % n;}
	if (p == 1) return 1;
	while (p != n - 1 && --r) {p = u128(p) * p % n;}
	return p == n - 1;
}
// bases obtained from
// https://miller-rabin.appspot.com/
bool dmr32(u32 n) {
	if (n < 49141) return mr32(n, 921211727);
	if (n < 316349281) return mr32(n, 11000544) && mr32(n, 31481107);
	return mr32(n, 2) && mr32(n, 7) && mr32(n, 61);
}
bool dmr64(u64 n) {
	if (n <= 0xFFFFFFFF) return dmr32(n);
	if (n < 350269456337) mr64(n, 4230279247111683200) &&
		mr64(n, 14694767155120705706u) && mr64(n, 16641139526367750375u);
	if (n < 55245642489451) mr64(n, 2) && mr64(n, 141889084524735) &&
		mr64(n, 1199124725622454117) && mr64(n, 11096072698276303650u);
	if (n < 7999252175582851) mr64(n, 2) && mr64(n, 4130806001517) &&
		mr64(n, 149795463772692060) && mr64(n, 186635894390467037) &&
		mr64(n, 3967304179347715805);
	if (n < 585226005592931977) mr64(n, 2) && mr64(n, 123635709730000) &&
		mr64(n, 9233062284813009) && mr64(n, 43835965440333360) &&
			mr64(n, 761179012939631437) && mr64(n, 1263739024124850375);
	return mr64(n, 2) && mr64(n, 325) && mr64(n, 9375) && mr64(n, 28178) &&
		mr64(n, 450775) && mr64(n, 9780504) && mr64(n, 1795265022);
}
