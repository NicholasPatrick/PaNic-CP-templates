#include <cstdio>
#include <queue>
#include <cstdint>
#include <functional>

template<typename T, class BinaryOperation=std::plus<T>>
class static_range{
	uint32_t n;
	std::vector<T> content;
	static uint32_t fastlog(uint32_t x){
		return 31-__builtin_clz(x);
	}
public:
	static_range(std::vector<T> a):n(a.size()){
		content=move(a);
		
	}
};