auto match(u32 l, u32 r, const vector<pair<u32, u32>>& e) {
	g_dir<true> g(l); vector<u32> rl(r, -1); vector<bool> lr(l, 0), vi; bool f;
	for (auto [u, v] : e)
		if (!~(rl[v] + lr[u])) lr[rl[v] = u] = 1; else g.add_edge(u, v);
	auto dfs = [&](auto f, u32 u) -> bool {
		vi[u] = 1;
		for (auto it = g[u].begin(); it != g[u].end(); ++it) {
			u32 v = *it;
			if (!~rl[v]) {rl[v] = u; g.erase(it); return 1;}
		}
		for (auto it = g[u].begin(); it != g[u].end(); ++it) {
			u32 v = *it;
			if (!vi[rl[v]] && f(f, rl[v])) {g.add_edge(rl[v], v);
				rl[v] = u; g.erase(it); return 1;}
		}
		return 0;
	};
	bool c; do {
		c = 0; vi.assign(l, 0);
		for (u32 u = l; u--;) c |= !lr[u] && (lr[u] = dfs(dfs, u));
	} while (c);
	vector<pair<u32, u32>> ret;
	for (u32 v = r; v--;) if (~rl[v]) ret.emplace_back(rl[v], v);
	return ret;
}