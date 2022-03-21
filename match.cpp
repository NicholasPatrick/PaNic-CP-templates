auto match(u32 l, u32 r, const vector<pair<u32, u32>>& e) {
	vector<u32> rl(r, -1), d(l); vector<bool> lr(l, 0), vi; bool f;
	for (auto [u, v] : e) {
		++d[u];
		if (!~(rl[v] + lr[u])) lr[rl[v] = u] = 1;
	}
	vector<vector<u32>> g(l); for (u32 i = l; i--;) g[i].reserve(d[i]);
	for (auto [u, v] : e) g[u].push_back(v);
	auto dfs = [&](auto f, u32 u) -> bool {
		vi[u] = 1;
		for (auto it = g[u].begin(); it != g[u].end(); ++it) {
			u32 v = *it;
			if (!~rl[v]) {rl[v] = u; return 1;}
		}
		for (auto it = g[u].begin(); it != g[u].end(); ++it) {
			u32 v = *it;
			if (!vi[rl[v]] && f(f, rl[v])) {
				g.add_edge(rl[v], v); rl[v] = u; return 1;
			}
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
