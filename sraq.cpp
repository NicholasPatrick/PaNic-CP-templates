template<typename T>
class sraq {
	vector<T> v;
public:
	sraq(vector<T> a) {
		u32 n = a.size(); v.resize(n * 2 - 1);
		copy(bend(a), v.begin() + (n - 1));
		for (u32 i = n; --i;) {v[i - 1] = v[2 * i - 1] + v[2 * i];}
	}
	T qry(u32 l, u32 r) {
		u32 n = v.size() + 1 >> 1; vector<u32> s, q;
		for (l += n - 1, r += n - 1; l < r; l = l - 1 >> 1, r = r - 1 >> 1) {
			if (~l & 1) s.push_back(l++); if (~r & 1) q.push_back(--r);
		} s.insert(s.end(), rbend(q)); T t = v[s[0]];
		for (u32 i = 1; i < s.size(); i++) t += v[s[i]]; return t;
	}
};
