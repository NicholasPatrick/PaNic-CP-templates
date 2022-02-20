template<class T>
class disjoint_sparse {
	u32 n; vector<T> v;
	static u32 fastlog(u32 x) {return 31 - __builtin_clz(x);}
public:
	disjoint_sparse(vector<T> a) : n(a.size()) {
		swap(v, a); if (n <= 1) return; u32 levels = fastlog(n - 1) + 1;
		v.resize(n * levels, v[0]);
		for (u32 i = n, j = 2; i < v.size(); i += n, j <<= 1) {
			for (u32 k = j; k < n; k += j) {
				v[i + k] = v[k];
				while (++k & j && k < n) v[i + k] = v[i + k - 1] + v[k];
			}
			for (u32 k = j - 1; k < n; k += j * 3) {
				v[i + k] = v[k];
				while (~--k & j) v[i + k] = v[k] + v[i + k + 1];
			}
		}
	}
	const T& operator[](u32 x) const {return v[x];}
	T qry(u32 l, u32 r) const {
		if (l == --r) return v[l]; u32 level = fastlog(l ^ r) * n;
		return v[level + l] + v[level + r];
	}
};
