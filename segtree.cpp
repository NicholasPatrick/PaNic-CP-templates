#include <queue>
#include <cstdint>
#include <cassert>

template<typename T>
class segtree{
	uint32_t n;
	std::vector<T> content;
public:
	segtree(std::vector<T> init):n(init.size()){
		content.resize(n*2-1);
		copy(init.begin(), init.end(), content.begin()+n-1);
		for(uint32_t i = n-1; i--;)
			content[i]=content[i<<1|1]+content[i+1<<1];
	}
	const T& operator[](uint32_t x)const{
		return content[x+n-1];
	}
	const T& at(uint32_t x)const{
		return content.at(x+n-1);
	}
	void update(uint32_t x, T v){
		content[x+=n-1]=v;
		do{
			x>>=1;
			content[x]=content[x<<1|1]+content[x+1<<1];
		}while(x);
	}
	T query(uint32_t l, uint32_t r)const{
		T retl, retr;
		for(l+=n-1, r+=n-1; l<r; l=l-1>>1, r=r-1>>1){
			if(~l&1)
				retl=retl+content[l++];
			if(~r&1)
				retr=content[--r]+retr;
		}
		return retl+retr;
	}
};