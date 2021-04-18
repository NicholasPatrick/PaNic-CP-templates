#include <queue>
#include <cstdint>

template<typename T>
class prefbit{
	uint32_t n;
	std::vector<T> content;
	inline static uint32_t up(uint32_t x){
		return x|x+1;
	}
	inline static uint32_t down(uint32_t x){
		return x-(x+1&~x);
	}
public:
	prefbit():n(0){}
	prefbit(uint32_t n):n(n), content(n){}
	void build(){
		for(uint32_t i = 0; i < n; i ++){
			if(up(i)<n)
				content[up(i)]=content[i]+content[up(i)];
		}
	}
	void update(uint32_t x, T y){
		for(; x < n; x=up(x))
			content[x]=y+content[x];
	}
	T query(uint32_t x){
		T ret;
		for(; x!=-1; x=down(x))
			ret=ret+content[x];
		return ret;
	}
	T operator[](uint32_t x){
		T ret;
		for(; x!=-1; x=down(x))
			ret=ret+content[x];
		return ret;
	}
};