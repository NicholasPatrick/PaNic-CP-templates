#include <bitset>
#include <cmath>
#include <cstdint>

std::bitset<256> filter1;
std::bitset<33619968> filter2;
struct prec_squareCheck { prec_squareCheck() {
	filter1.set();
	for (uint32_t i = 0; i < 128; i++)
		filter1[i * i & 255] = false;
	filter2.set();
	{
		uint32_t i = 0, sq = 0;
		while (i < 0x800000) {
			filter2[sq] = false;
			sq += (i << 1) + 1;
			if (sq >= 0xffffff)
				sq -= 0xffffff;
			i++;
		}
	}
	for (uint32_t i = 0x1000000; i < 33619968; i++)
		filter2[i] = filter2[i - 0x1000000];
} } _prec_squareCheck;
uint32_t squareCheck(uint32_t n) {
	if (filter1[n & 255] ||
		filter2[(n & 0xffffff) + (n >> 24 & 0xffffff)]
	)
		return -1;
	uint32_t s = sqrt(n) + 0.5;
	if (s * s == n)
		return s;
	return -1;
}
uint64_t squareCheckll(uint64_t n) {
	if (filter1[n & 255] ||
		filter2[(n & 0xffffff) + (n >> 24 & 0xffffff) + (n >> 48)]
	)
		return -1;
	uint64_t s = sqrt(n) + 0.5;
	if (s * s == n)
		return s;
	return -1;
}