const u32 BASE = 123;
const u32 H_U = 2, MAX_LEN = 2e6;
const u32 H_PRI[] = {
	0x3fffffdd, 1062599999, 1047899999, 1031999999,
	// beyond this point, I'm just flexxing the primes I memorised
	1027799999, 1018199999, 1000000007
};
u32 h_pow[H_U][MAX_LEN + 1];
struct __h_pow {__h_pow() {
	for (u32 i = H_U; i--;) {
		h_pow[i][0] = 1;
		for (u32 j = 0; j < MAX_LEN; ++j)
			h_pow[i][j + 1] = (u64) h_pow[i][j] * BASE % H_PRI[i];
	}
}} ___h_pow;
using hash_t = array<u32, H_U>;
class string_hash {
	vector<hash_t> p;
public:
	string_hash(const string& s) {
		u32 n = s.size(); p.resize(n + 1); p[0].fill(0);
		for (u32 i = H_U; i--;) for (u32 j = 0; j < n; ++j)
			p[j + 1][i] = (p[j][i] + (u64) h_pow[i][j] * s[j]) % H_PRI[i];
	}
	hash_t substr(u32 l, u32 r) {
		hash_t ret;
		for (u32 i = H_U; i--;)
			ret[i] = u64(p[r][i] - p[l][i] + H_PRI[i]) *
				h_pow[i][MAX_LEN - l] % H_PRI[i];
		return ret;
	}
};
