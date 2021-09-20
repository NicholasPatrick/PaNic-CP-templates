#include <cstdio>
#include <algorithm>
#include <cstdint>

// minimalistic
// template<uint32_t mod>
// struct shortMint {
// 	uint32_t a;
// 	constexpr inline shortMint(uint32_t a = 0) : a(a) {}
// 	static shortMint read();
// 	constexpr inline shortMint operator+(shortMint rhs) const {
// 		uint32_t r = a + rhs.a;
// 		return r < mod ? r : r - mod;
// 	}
// 	constexpr inline shortMint operator-(shortMint rhs) const {
// 		uint32_t r = a - rhs.a;
// 		return r < mod ? r : r + mod;
// 	}
// 	constexpr inline shortMint operator-() const {
// 		return a ? mod - a : 0;
// 	}
// 	constexpr inline shortMint operator*(shortMint rhs) const {
// 		return (uint64_t)a * rhs.a % mod;
// 	}
// 	constexpr inline shortMint& operator+=(shortMint rhs) {
// 		a += rhs.a;
// 		if (a >= mod)
// 			a -= mod;
// 		return *this;
// 	}
// 	constexpr inline shortMint& operator-=(shortMint rhs) {
// 		a -= rhs.a;
// 		if (a >= mod)
// 			a += mod;
// 		return *this;
// 	}
// 	constexpr inline shortMint& operator*=(shortMint rhs) {
// 		a = (uint64_t)a * rhs.a % mod;
// 		return *this;
// 	}
// 	constexpr inline bool operator==(shortMint rhs) const {
// 		return a == rhs.a;
// 	}
// 	constexpr inline bool operator!=(shortMint rhs) const {
// 		return a != rhs.a;
// 	}
// };
// template<uint32_t mod>
// inline shortMint<mod> shortMint<mod>::read() {
// 	uint32_t a;
// 	scanf("%u", &a);
// 	return a;
// }
// using mint = shortMint<998244353>;
// using mint = shortMint<1000000007>;

// fast operations, slow read and write
template<uint32_t mod>
class montgomeryMint {
private:
	static_assert(mod&1, "montgomery modulus must be odd");
	static constexpr uint32_t get_r2() {
		return (- (uint64_t) mod) % mod;
	}
	static constexpr uint32_t r2 = get_r2();
	static constexpr uint32_t get_m(){
		uint32_t ret = mod;
		ret *= 2 - ret * mod;
		ret *= 2 - ret * mod;
		ret *= 2 - ret * mod;
		ret *= 2 - ret * mod;
		return - ret;
	}
	static constexpr uint32_t m = get_m();
public:
	static constexpr inline uint32_t reduce(uint64_t t) {
		uint32_t ret = t + uint64_t((uint32_t) t * m) * mod >> 32;
		return ret < mod ? ret : ret - mod;
	}
	static constexpr inline uint32_t montgomerise(uint32_t x) {
		return reduce((uint64_t) r2 * x);
	}
private:
	uint32_t a;
	constexpr inline montgomeryMint(uint32_t a) : a(a) {}
public:
	constexpr inline montgomeryMint() : a(0) {}
	static montgomeryMint read();
	constexpr static montgomeryMint mulr(uint32_t a);
	constexpr inline montgomeryMint operator+(montgomeryMint rhs) const {
		uint32_t ret = a + rhs.a;
		return ret < mod ? ret : ret - mod;
	}
	constexpr inline montgomeryMint operator-(montgomeryMint rhs) const {
		uint32_t ret = a - rhs.a;
		return ret < mod ? ret : ret + mod;
	}
	constexpr inline montgomeryMint operator-() const {
		return a ? mod - a : 0;
	}
	constexpr inline montgomeryMint operator*(montgomeryMint rhs) const {
		return reduce((uint64_t) a * rhs.a);
	}
	template<typename T>
	constexpr inline montgomeryMint operator*(T rhs) const {
		static_assert(std::is_integral_v<T>,
			"montgomeryMint may only be multiplied by integer types or itself");
		return operator*(montgomeryMint::mulr(rhs));
	}
	constexpr inline montgomeryMint& operator+=(montgomeryMint rhs) {
		a += rhs.a;
		if (a >= mod)
			a -= mod;
		return *this;
	}
	constexpr inline montgomeryMint& operator-=(montgomeryMint rhs) {
		a -= rhs.a;
		if (a >= mod)
			a += mod;
		return *this;
	}
	constexpr inline montgomeryMint& operator*=(montgomeryMint rhs) {
		a = reduce(a * rhs.a);
		return *this;
	}
	constexpr inline bool operator==(montgomeryMint rhs) const {
		return a == rhs.a;
	}
	constexpr inline bool operator!=(montgomeryMint rhs) const {
		return a != rhs.a;
	}
	constexpr inline uint32_t eval() const {
		return reduce(a);
	}
};
template<uint32_t mod>
constexpr inline montgomeryMint<mod> montgomeryMint<mod>::mulr(uint32_t a) {
	return montgomeryMint(montgomerise(a));
}
template<uint32_t mod>
inline montgomeryMint<mod> montgomeryMint<mod>::read() {
	uint32_t v;
	scanf("%u", &v);
	return montgomeryMint::mulr(v);
}
using mint = montgomeryMint<998244353>;
// using mint = fastMint<1000000007>;

int main() {
	mint a = mint::mulr(5), b = mint::mulr(7);
	a += b;
	printf("%u\n", a.eval());
}