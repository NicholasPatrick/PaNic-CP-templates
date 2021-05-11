#include <queue>
#include <cstdint>
#include <cassert>

template<typename T>
class disjoint_sparse{
	uint32_t n;
	std::vector<T> content;
	static uint32_t fastlog(uint32_t x){
		return 31-__builtin_clz(x);
	}
public:
	disjoint_sparse(std::vector<T> a):n(a.size()){
		content=std::move(a);
		if(n<=1)return;
		uint32_t levels=fastlog(n-1)+1;
		content.resize(n*levels, content[0]);
		for(uint32_t i=n, j=2; i < content.size(); i+=n, j<<=1){
			for(uint32_t k = j; k < n; k += j){
				content[i+k]=content[k];
				for(k ++; k&j and k<n; k ++)
					content[i+k]=content[i+k-1]+content[k];
			}
			for(uint32_t k = j-1; k < n; k += j*3){
				content[i+k]=content[k];
				for(k --; ~k&j; k --)
					content[i+k]=content[k]+content[i+k+1];
			}
		}
	}
	const T& operator[](uint32_t x)const{
		return content[x];
	}
	const T& at(uint32_t x)const{
		return content.at(x);
	}
	T query(uint32_t l, uint32_t r)const{
		assert(l<r);
		r--;
		if(l==r)
			return content[l];
		uint32_t level=fastlog(l^r)*n;
		return content[level+l]+content[level+r];
	}
};