template<bool scaling = false, class f_t = u64, class al_t>
auto dinitz(const al_t& al, u32 s, u32 t) {
	using w_t = typename al_t::value_type::value_type::second_type;
	u32 v = al.size(); vector<vector<u32>> yl(v);
	vector<vector<w_t>> cap(v, vector<w_t>(v, 0)), flow = cap;
	for (u32 x = v; x--;) for (const auto& [y, w] : al[x]) {
		if (w == 0) continue;
        if (!(cap[x][y] + cap[x][y])) yl[x].push_back(y), yl[y].push_back(x);
        cap[x][y] += w;
	}
    vector<u32> q(v, s), dl(v), dist;
	for (u32 L = scaling ? 32 : 1; L--;)
	for (;;) {
        dist.assign(v, -1); u32 qfr = dist[s] = 0, qba = 1;
		while (qfr < qba) {
            u32 x = q[qfr++];
            for (u32 y : yl[x]) if (dist[y] == -1 && cap[x][y] >> L)
                dist[q[qba++] = y] = dist[x] + 1;
		}
        if (dist[t] == -1) break;
        for (u32 x = v; x--;) dl[x] = yl[x].size();
		auto dfs = [&](auto self, u32 x, u32 f) -> w_t {
            if (x == t) return f;
			while (dl[x]) {
                u32 y = yl[x][dl[x] - 1];
				if (dist[y] != dist[x] + 1 || cap[x][y] >> L == 0) {
                    --dl[x]; continue;
                }
                u32 r = self(self, y, min(f, cap[x][y]));
                if (r) {
				    cap[x][y] -= r; cap[y][x] += r; flow[x][y] += r;
					if (cap[x][y] >> L == 0) --dl[x];
                    return r;
                } else --dl[x];
			}
            return 0;
		};
        while (dfs(dfs, s, numeric_limits<w_t>::max()));
	}
    f_t ft = 0; for (w_t w : flow[s]) ft += w;
    vector<vector<w_t>> fd(v);
	for (u32 x = v; x--;) for (const auto& [y, w] : al[x]) {
        w_t f = min(flow[x][y], w); flow[x][y] -= f; fd[x].push_back(f);
    }
    return pair(ft, fd);
}