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
