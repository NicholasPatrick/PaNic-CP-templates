// returns pair of max-flow and source side of min-cut
template<bool scaling = false, class f_t = u64, class al_t>
auto mincut(const al_t& al, u32 s, u32 t) {
	using w_t = typename al_t::value_type::value_type::second_type;
	u32 v = al.size();
	vector<u32> st(v + 1, 0), q(v, s), dist, cd;
	vector<tuple<u32, u32, w_t, w_t>> el; f_t ft = 0;
	{
		vector<pair<u32, u32>> sel;
		for (u32 x = v; x--;) for (auto [y, w] : al[x])
			if (w) sel.emplace_back(x, y), sel.emplace_back(y, x);
		sort(bend(sel)); sel.resize(st[v] = unique(bend(sel)) - sel.begin());
		el.resize(st[v], {0, 0, 0, 0});
		for (u32 k = 0, x = 0; k < st[v]; ++k) {
			auto &[y, i, _, __] = el[k];
			while (x < sel[k].first) st[++x] = k;
		}
		for (u32 k = 0; k < st[v]; ++k) {
			auto &[y, i, _, __] = el[k];
			y = sel[k].second;
			i = lower_bound(sel.begin() + st[y], sel.begin() + st[y + 1],
				sel[k].first, [&](pair<u32, u32> &l, u32 r)
				{return l.second < r;}) - sel.begin();
		}
		for (u32 x = v; x--;) for (auto [y, w] : al[x]) {
			get<2>(el[lower_bound(sel.begin() + st[x], sel.begin() + st[x + 1],
				y, [&](pair<u32, u32> &l, u32 r) {return l.second < r;}) -
				sel.begin()]) += w;
		}
	}
	for (u32 L = scaling ? sizeof(w_t) * 8 : 1; L--;)
	for (;;) {
		dist.assign(v, -1); u32 qfr = dist[s] = 0, qba = 1;
		while (qfr < qba) {
			u32 x = q[qfr++];
			for (u32 i = st[x + 1]; i-- > st[x];) {
				auto [y, _, c, __] = el[i];
				if (!~dist[y] && c >> L) dist[q[qba++] = y] = dist[x] + 1;
			}
		}
		if (!~dist[t]) {
			q.resize(qba);
			return make_pair(ft, q);
		}
		cd = st;
		auto dfs = [&](auto self, u32 x, w_t m) -> w_t {
			if (x == t) return m;
			while (cd[x] != st[x + 1]) {
				auto &[y, i, c, f] = el[cd[x]];
				if (dist[y] != dist[x] + 1 || c >> L == 0) {++cd[x]; continue;}
				w_t r = self(self, y, min(m, c));
				if (r) {
					c -= r; get<2>(el[i]) += r; f += r;
					if (c >> L == 0) ++cd[x];
					return r;
				} else ++cd[x];
			}
			return 0;
		};
		for (;;) {
			w_t cf = dfs(dfs, s, numeric_limits<w_t>::max());
			if (!cf) break; ft += cf;
		}
	}
}
