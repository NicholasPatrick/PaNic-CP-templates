template <class T>
T mulexp(T a, T b, u32 e) {
	for (; e; e >>= 1, b *= b) if (e & 1) a *= b; return a;
}
template <class T>
T expmul(T b, u32 e, T a) {
	for (; e; e >>= 1, b *= b) if (e & 1) a = b * a; return a;
}