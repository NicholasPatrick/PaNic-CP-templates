#include <cstdint>
#include <queue>

class dsu {
	std::vector<uint32_t> par;
	// if the value is negative, it represents size
	// otherwise, it represents parent
public:
	dsu() {}
	dsu(uint32_t n) : par(n, -1u) {}
	uint32_t operator[](uint32_t x) {
		return par[x] & 1u << 31 ? x : par[x] = operator[](par[x]);
	}
	uint32_t at(uint32_t x) {
		return par[x] & 1u << 31 ? x : par[x] = at(par[x]);
	}
	bool join(uint32_t x, uint32_t y) {
		if ((x = operator[](x)) == (y = operator[](y)))
			return false;
		if (par[x] < par[y]) {
			par[x] += par[y];
			par[y] = x;
		} else {
			par[y] += par[x];
			par[x] = y;
		}
		return true;
	}
	void resize(uint32_t n) {
		par.resize(n, -1u);
	}
	void assign(uint32_t n) {
		par.assign(n, -1u);
	}
};