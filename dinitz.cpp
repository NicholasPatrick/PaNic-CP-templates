#include <cstdint>
#include <cstdio>
#include <queue>

struct diredge {
	uint32_t f, t, c;
	diredge() {}
	diredge(uint32_t f, uint32_t t, uint32_t c) : f(f), t(t), c(c) {}
};
struct branch {
	uint32_t t, c, r;
	branch(uint32_t t, uint32_t c, uint32_t r) : t(t), c(c), r(r) {}
};
template<bool scaling = false>
pair<uint64_t, vector<uint32_t>> dinitz(uint32_t v, uint32_t s, uint32_t t,
	const vector<diredge>& edges) {
	vector<vector<branch>> adjLis(v);
	for (auto& i: edges) {
		uint32_t r1 = adjLis[i.f].size(), r2 = adjLis[i.t].size();
		adjLis[i.f].emplace_back(i.t, i.c, r2);
		adjLis[i.t].emplace_back(i.f, 0, r1);
	}

	uint64_t total_flow = 0;
	vector<uint32_t> search;
	search.reserve(v);
	uint32_t search_front=0;
	vector<uint32_t> dist;
	vector<uint32_t> dfsIndex;
	for (uint32_t L = scaling ? 32 : 1; L--; )
	for (; ; ) {
		//bfs
		dist.assign(v, 0);
		dist[t] = v;
		search.clear();
		search.push_back(t);
		search_front = 0;
		while (search_front < search.size()) {
			uint32_t x = search[search_front++];
			for (auto y: adjLis[x]) {
				if (dist[y.t] == 0 && adjLis[y.t][y.r].c >> L) {
					dist[y.t] = dist[x] - 1;
					search.push_back(y.t);
				}
			}
		}
		if (dist[s] == 0)
			break;
		//dfs
		dfsIndex.assign(v, 0);
		for (; ; ) {
			search.clear();
			search.push_back(s);
			while (!search.empty() && search.back() != t) {
				uint32_t x = search.back();
				for (; dfsIndex[x] < adjLis[x].size(); dfsIndex[x]++) {
					auto& y = adjLis[x][dfsIndex[x]];
					if (dist[y.t] == dist[x] + 1 && y.c && dfsIndex[y.t] < adjLis[y.t].size()) {
						search.push_back(y.t);
						break;
					}
				}
				if (search.back() == x)
					search.pop_back();
			}
			if (search.empty())
				break;
			uint32_t current_flow = -1;
			search.pop_back();
			for (uint32_t i : search) {
				auto& y = adjLis[i][dfsIndex[i]];
				current_flow = min(current_flow, y.c);
			}
			for (uint32_t i : search) {
				auto& y = adjLis[i][dfsIndex[i]];
				y.c -= current_flow;
				adjLis[y.t][y.r].c += current_flow;
			}
			total_flow += current_flow;
		}
	}
	vector<uint32_t> flow;
	flow.reserve(edges.size());
	dfsIndex.assign(v, 0);
	for (auto& i: edges) {
		flow.push_back(adjLis[i.t][dfsIndex[i.t]].c);
		dfsIndex[i.f]++;
		dfsIndex[i.t]++;
	}
	return make_pair(total_flow, flow);
}
