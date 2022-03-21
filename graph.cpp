template<bool lazy = false>
class g_dir {
	class lit {
		g_dir &g; friend class g_dir; u32 i;
		public: lit(g_dir &g, u32 i) : g(g), i(i) {}
		const u32& operator*() const {return get<3>(g.pnuv[i]);}
		lit& operator++() {i = get<0>(g.pnuv[i]); return *this;}
		lit operator++(int) {auto ret = *this; ++*this; return ret;}
		bool operator!=(lit rhs) const {return i != rhs.i;}
	};
	class lis {
		g_dir &g; u32 u; public: lis(g_dir &g, u32 u) : g(g), u(u) {}
		lit begin() const {return lit(g, g.las[u]);}
		lit end() const {return lit(g, -1);}
	};
	vector<u32> las; vector<tuple<u32, u32, u32, u32>> pnuv;
public:
	g_dir(u32 v) : las(v) {for (u32 i = v; i--;) las[i] = -1;}
	u32 add_edge(u32 u, u32 v) {
		u32 r = pnuv.size(), &l = las[u]; if (~l) get<1>(pnuv[l]) = r;
		pnuv.emplace_back(l, -1, u, v); return l = r;
	}
	pair<u32, u32> erase(u32 i) {
		auto &[p, n, u, v] = pnuv[i]; if (~p) get<1>(pnuv[p]) = n;
		if (~n) get<0>(pnuv[n]) = p; else las[u] = p;
		if constexpr (lazy) return {u, v};
		if (i + 1 == pnuv.size()) return {u, v};
		pair<u32, u32> ret = {u, v}; pnuv[i] = pnuv.back(); pnuv.pop_back();
		if (~n) get<0>(pnuv[n]) = i; else las[u] = i;
		if (~p) get<1>(pnuv[p]) = i; return ret;
	}
	pair<u32, u32> erase(lit iti) {return erase(iti.i);}
	lis operator[](u32 u) {return lis(*this, u);}
};
