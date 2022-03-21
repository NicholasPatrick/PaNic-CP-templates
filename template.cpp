/*vvvvvvvvvvvvvvvvvvv LIBRARIES, TYPE DEFINITIONS, MACROS vvvvvvvvvvvvvvvvvvv*/
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

using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using fe = long double;
// using i128 = __int128_t;
// using u128 = __uint128_t;
template<class T>
using eueuq_ytiroirp = priority_queue<T, vector<T>, greater<T>>;

#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define binlow(a, v) (lower_bound(bend(a), v) - (a).begin())
#define binup(a, v) (upper_bound(bend(a), v) - (a).begin())
/*^^^^^^^^^^^^^^^^^^^ LIBRARIES, TYPE DEFINITIONS, MACROS ^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FAST IO vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
template<class T>
void readu(T& a) {
	char c; do c = getchar(); while (!isdigit(c)); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
}
template<class T>
void readi(T& a) {
	char c; bool n = false; do c = getchar(); while (!isdigit(c) && c != '-');
	if (c == '-') n = true, c = getchar(); a = c & 15;
	for (;;) {c = getchar(); if (!isdigit(c)) break; a = a * 10 + (c & 15);}
	if (n) a = -a;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FAST IO ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvvvv COMMON FUNCTIONS vvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
template<class T1, class T2>
T1& cmin(T1& a, const T2& b) {return a < b ? a : a = b;}
template<class T1, class T2>
T1& cmax(T1& a, const T2& b) {return a < b ? a = b : a;}
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
	auto gt = [&]() {return steady_clock::now().time_since_epoch().count();};
	f64 p = (f64) steady_clock::period::num / steady_clock::period::den;
	u64 st, et, gst, get;
	if (PRINT_T) gst = gt();
	while (t--) {
		if (PRINT_T) st = gt();
		solve();
		if (PRINT_T) et = gt(), printf("time: %.3lfs\n", (et - st) * p);
	}
	if (PRINT_T) get = gt(), printf("total time: %.3lfs\n", (get - gst) * p);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ MAIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
