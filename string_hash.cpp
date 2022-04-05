const u32 BASE = 456;
const u32 H_U = 2, MAX_LEN = 2e6;
const u32 H_PRI[] = {0x3fffffdd, 1031999999, 1000000007};
const lm32 H_LM[] = {0x3fffffdd, 1031999999, 1000000007};
u32 h_pow[H_U][MAX_LEN + 1];
struct __h_pow {__h_pow() {
	for (u32 i = H_U; i--;) {
		h_pow[i][0] = H_LM[i](1); h_pow[i][1] = H_LM[i](BASE);
		for (u32 j = 1; j < MAX_LEN; ++j)
			h_pow[i][j + 1] = H_LM[i].mul(h_pow[i][j], h_pow[i][1]);
	}
}} ___h_pow;
using hash_t = array<u32, H_U>;
class string_hash {
	vector<hash_t> p;
public:
	string_hash(const string& s) {
		u32 n = s.size(); p.resize(n + 1); p[0].fill(0);
		for (u32 i = H_U; i--;) for (u32 j = 0; j < n; ++j) {
			p[j + 1][i] = H_LM[i].add(H_LM[i].mul(h_pow[i][j], s[j]), p[j][i]);
		}
	}
	hash_t substr(u32 l, u32 r) {
		hash_t ret;
		for (u32 i = H_U; i--;)
			ret[i] = H_LM[i].mul(H_LM[i].sub(p[r][i], p[l][i]),
				h_pow[i][MAX_LEN - l]);
		for (u32 i = H_U; i--;) if (ret[i] >= H_PRI[i]) ret[i] -= H_PRI[i];
		return ret;
	}
	hash_t prefix(u32 x) {return substr(0, x);}
	hash_t suffix(u32 x) {return substr(p.size() - 1 - x, p.size() - 1);}
};
