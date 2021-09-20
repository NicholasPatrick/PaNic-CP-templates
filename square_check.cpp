#include <bitset>
#include <cmath>
#include <cstdint>

// modulo 256, filters 82% of non-squares
std::bitset<256> sqlookup1;
// modulo 4095, filters 91% of non-squares
std::bitset<8446> sqlookup2;
void preq_sqchecker() {
	sqlookup1.set();
	sqlookup2.set();
	for (uint32_t i = 128; i--;)
		sqlookup1[i * i & 255] = false;
	for (uint32_t i = 2048; i--;)
		sqlookup2[i * i % 4095] = false;
	for (uint32_t i = 4095; i < 8446; i++)
		sqlookup2[i] = sqlookup2[i - 4095];
}
uint32_t square_check(uint32_t n) {
	if (
		sqlookup1[n & 0xff] or
		sqlookup2[(n & 0xfff) + (n >> 12 & 0xfff) + (n >> 24)]
	)
		return -1;
	/*
		non-squares < 10000 which makes it here:
		585, 945, 1465, 1561, 1729, 2041, 2185, 2305, 2340, 2521, 2545, 2961,
		3145, 3241, 3409, 3649, 3745, 3780, 3865, 4081, 4369, 4585, 4705, 4729,
		5121, 5161, 5209, 5265, 5425, 5665, 5769, 5860, 5905, 6049, 6244, 6265,
		6409, 6601, 6721, 6769, 6841, 6916, 7081, 7281, 7345, 7609, 7641, 7849,
		8089, 8164, 8401, 8425, 8449, 8505, 8740, 8761, 8785, 8905, 9009, 9220,
		9265, 9360, 9361, 9529, 9585, 9961
		A total of 66
	*/
	uint32_t x = sqrt(n);
	if (x * x != n)
		printf("%u, ", n);
	return x * x == n ? x : -1;
}