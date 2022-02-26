template<class i_t = i64, class v_t = i64, class u_t = i32>
class fenuq {
	vector<i_t> c; vector<v_t> v;
public:
	fenuq(vector<i_t> indices) : c(move(indices)), v(c.size(), 0) {}
	void upd(i_t x, u_t y) {
		for (u32 i = binlow(c, x); i < v.size(); i |= -~i)v[i] += y;
	}
	v_t qry(i_t x) {
		v_t r = 0;
		for (u32 i = bindup(c, x); i; i -= i & -i) r += v[i - 1]; return r;
	}
};

template<class i_t = i64, class v_t = i64, class u_t = i32>
class fenqu {
	vector<i_t> c; vector<v_t> v;
public:
	fenqu(vector<i_t> indices) : c(move(indices)), v(c.size(), 0) {}
	void upd(i_t x, u_t y) {
		for (u32 i = binlow(c, x) + 1; i; i -= i & -i) v[i - 1] += y;
	}
	v_t qry(i_t x) {
		v_t r = 0;
		for (u32 i = binlow(c, x); i < v.size(); i |= -~i) r += v[i]; return r;
	}
};
