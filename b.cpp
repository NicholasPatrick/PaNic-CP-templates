/*vvvvvvvvvvvvvvvvvvv LIBRARIES, TYPE DEFINITIONS, MACROS vvvvvvvvvvvvvvvvvvv*/
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <type_traits>

using namespace std;

using namespace chrono;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class k_t, class m_t>
// using ordered_map = tree<k_t, m_t, less<T>, rb_tree_tag,
//	tree_order_statistics_node_update>;
// template<class T>
// using ordered_set = ordered_map<T, null_type>;

using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using fe = long double;
// using i128 = __int128_t;
// using u128 = __uint128_t;
template<class T>
using eueuq_ytiroirp = priority_queue<T, vector<T>, greater<T>>;

#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define binlow(a, v) (lower_bound(bend(a), v) - (a).begin())
#define binup(a, v) (upper_bound(bend(a), v) - (a).begin())
/*^^^^^^^^^^^^^^^^^^^ LIBRARIES, TYPE DEFINITIONS, MACROS ^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FAST IO vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
template<class T>
void readu(T& a) {
	char c; do c = getchar(); while (!isdigit(c)); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
}
template<class T>
void readi(T& a) {
	char c; bool n = false; do c = getchar(); while (!isdigit(c) && c != '-');
	if (c == '-') n = true, c = getchar(); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
	if (n) a = -a;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FAST IO ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv LIBRARY vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
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
auto hopcroft_karp(u32 l, u32 r, const vector<pair<u32, u32>>& e) {
	g_dir<true> g(l); vector<u32> rl(r, -1), lq, rq, ld, rd;
	vector<bool> lr(l, 0), vis; bool f; lq.reserve(l); rq.reserve(r);
	for (auto [u, v] : e)
		if (!~(rl[v] + lr[u])) lr[rl[v] = u] = 1; else g.add_edge(u, v);
	for (;;) {
		lq.clear(); rq.clear(); ld.assign(l, -1); rd.assign(r, -1); f = 0;
		for (u32 u = l; u--;) if (!lr[u]) ld[u] = 0, lq.push_back(u);
		for (u32 d = 0; !lq.empty();) {
			for (u32 u : lq) for (u32 v : g[u]) if (!~rd[v]) {
				rd[v] = d, rq.push_back(v); if (!~rl[v]) f = 1;
			}
			if (f) break;
			lq.clear(); ++d;
			for (u32 v : rq) {
				u32 u = rl[v]; if (!~ld[u]) ld[u] = d, lq.push_back(u);
			}
			rq.clear();
		}
		if (!f) break;
		auto dfs = [&](auto f, u32 u) -> bool {
			vis[u] = 1;
			for (auto it = g[u].begin(); it != g[u].end(); ++it) {
				u32 v = *it; if (ld[u] != rd[v]) continue;
				if (!~rl[v]) {a: rl[v] = u; g.erase(it); return 1;}
				if (!vis[rl[v]] && f(f, rl[v])) {g.add_edge(rl[v], v); goto a;}
			}
			return 0;
		};
		vis.assign(l, 0); for (u32 u = l; u--;) if (!lr[u]) lr[u] = dfs(dfs, u);
	}
	vector<pair<u32, u32>> ret;
	for (u32 v = r; v--;) if (~rl[v]) ret.emplace_back(rl[v], v);
	return ret;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ LIBRARY ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv MAIN vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
void solve() {
	u32 l, r, m; readu(l); readu(r); readu(m);
	vector<pair<u32, u32>> e(m); for (auto &[a, b] : e) readu(a), readu(b);
	auto rec = hopcroft_karp(l, r, e);
	printf("%lu\n", rec.size());
	for (auto [c, d] : rec) printf("%u %u\n", c, d);
}
int main() {
	u32 t = 1;
	// readu(t);
	static const bool PRINT_T = 0;
	auto gt = [&]() {return steady_clock::now().time_since_epoch().count();};
	f64 p = (f64) steady_clock::period::num / steady_clock::period::den;
	u64 st, et, gst, get;
	if (PRINT_T) gst = gt();
	while (t--) {
		if (PRINT_T) st = gt();
		solve();
		if (PRINT_T) et = gt(), printf("time: %.3lfs\n", (et - st) * p);
	}
	if (PRINT_T) get = gt(), printf("total time: %.3lfs\n", (get - gst) * p);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ MAIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
