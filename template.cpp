/*vvvvvvvvvvvvvvvvvvv LIBRARIES, TYPE DEFINITIONS, MACROS vvvvvvvvvvvvvvvvvvv*/
#include <numeric>
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <type_traits>

using namespace std;

using namespace chrono;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class k_t, class m_t>
// using ordered_map = tree<k_t, m_t, less<T>, rb_tree_tag,
//	tree_order_statistics_node_update>;
// template<class T>
// using ordered_set = ordered_map<T, null_type>;

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using fe = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
template<class T>
using eueuq_ytiroirp = priority_queue<T, vector<T>, greater<T>>;

#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define binlow(a, v) u32(lower_bound(bend(a), v) - (a).begin())
#define binup(a, v) u32(upper_bound(bend(a), v) - (a).begin())
#define mod1(a, b) (a < b ? a : a - b)
/*^^^^^^^^^^^^^^^^^^^ LIBRARIES, TYPE DEFINITIONS, MACROS ^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FAST IO vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
template<class T>
void readu(T &a) {
	char c; do c = getchar(); while (!isdigit(c)); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
}
template<class T>
void readi(T &a) {
	char c; bool n = false; do c = getchar(); while (!isdigit(c) && c != '-');
	if (c == '-') n = true, c = getchar(); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
	if (n) a = -a;
}
template<class T>
void reads(T &s) {
	char c; do c = getchar(); while (!isgraph(c));
	do s.push_back(c), c = getchar(); while (isgraph(c));
}
template<class T>void printui(T);
template<> void printui(u8 x) {printf("%hhu\n", x);}
template<> void printui(u16 x) {printf("%hu\n", x);}
template<> void printui(u32 x) {printf("%u\n", x);}
template<> void printui(u64 x) {printf("%llu\n", x);}
template<> void printui(i8 x) {printf("%hhd\n", x);}
template<> void printui(i16 x) {printf("%hd\n", x);}
template<> void printui(i32 x) {printf("%d\n", x);}
template<> void printui(i64 x) {printf("%lld\n", x);}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FAST IO ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvv COMMON FUNCTIONS vvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
template<class T1, class T2>
T1& cmin(T1 &a, const T2 &b) {return a < b ? a : a = b;}
template<class T1, class T2>
T1& cmax(T1 &a, const T2 &b) {return a < b ? a = b : a;}
u64 gt() {return steady_clock::now().time_since_epoch().count();};
const f64 gtp = (f64) steady_clock::period::num / steady_clock::period::den;
void sleep(long double t) {t = t / gtp + gt(); while (gt() < t);}
template<class T>
T &sue(T &x) {sort(bend(x)); x.erase(unique(bend(x)), x.end()); return x;}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^ COMMON FUNCTIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv LIBRARY vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
// copy prewritten code here
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ LIBRARY ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv MAIN vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
void solve() {
}
int main() {
	u32 t = 1;
	// readu(t);
	static const bool PRINT_T = 0;
	u64 st, et, gst, get;
	if (PRINT_T) gst = gt();
	while (t--) {
		if (PRINT_T) st = gt();
		solve();
		if (PRINT_T) et = gt(), printf("time: %.6lfs\n", (et - st) * gtp);
	}
	if (PRINT_T) get = gt(), printf("total time: %.6lfs\n", (get - gst) * gtp);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ MAIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
