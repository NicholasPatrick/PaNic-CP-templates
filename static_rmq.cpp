#include <cstdint>
#include <queue>

template<typename T, class Compare=std::less<T>>
class static_rmq{
	uint32_t n, m;
	std::vector<T> original;
	std::vector<uint32_t> masks;
	// masks take advantage of __builtin_ctz to quickly find minimum in blocks
	// of 32 values
	std::vector<uint32_t> sparse;
	static uint32_t fastlog(uint32_t x){
		return 31-__builtin_clz(x);
	}
	bool indexCompare(uint32_t a, uint32_t b)const{
		return Compare()(original[a], original[b]);
	}
	uint32_t indexMin(uint32_t a, uint32_t b)const{
		return Compare()(original[a], original[b])?a:b;
	}
public:
	static_rmq(std::vector<T> a):n(a.size()), m((n+31)/32), original(move(a)),
		masks(n){
		for(uint32_t i=0; i<n; i+=32){
			uint32_t fend=std::min(n, i+32);
			uint32_t val=masks[i]=1;
			// val is a mask that acts as a stack
			for(uint32_t j=i+1; j<fend; j++){
				while(val and indexCompare(j, i+fastlog(val)))
					val^=1u<<fastlog(val);
				masks[j]=val|=1u<<j-i;
			}
		}
		// data structure on top of blocks only if necessary
		if(n>64){
			uint32_t layers=(fastlog(m-1)+1);
			sparse.reserve(m*layers);
			for(uint32_t i=0; i<n; i+=32){
				uint32_t fend=std::min(n, i+32);
				sparse[i/32]=i;
				for(uint32_t j=i+1; j<fend; j++)
					sparse[i/32]=indexMin(sparse[i/32], j);
			}
			for(uint32_t I=0; I+1<layers; I++){
				for(uint32_t i=0; i+(2u<<I)<=m; i++)
					sparse[I*m+m+i]=indexMin(
						sparse[I*m+i],
						sparse[I*m+i+(1u<<I)]
					);
			}
		}
	}
	const T& operator[](uint32_t x)const{
		return original[x];
	}
	uint32_t query(uint32_t l, uint32_t r)const{
		r--;
		if(l/32==r/32)
			return __builtin_ctz(masks[r]>>l%32)+l;
		uint32_t ret=indexMin(
			__builtin_ctz(masks[r])+(r&~31),
			__builtin_ctz(masks[l|31]>>l%32)+l
		);
		l=l/32+1, r/=32;
		if(l==r)
			return ret;
		uint32_t w=fastlog(r-l);
		return indexMin(ret, indexMin(sparse[w*m+l], sparse[w*m+r-(1u<<w)]));
	}
};