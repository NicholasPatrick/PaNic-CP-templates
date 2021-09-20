#include <cstdio>
#include <queue>
#include <cassert>
#include <cstdint>

template <typename T>
class matrix{
	uint32_t n, m;
	std::vector<T> content;
public:
	matrix():n(0), m(0){}
	matrix(uint32_t n, uint32_t m):n(n), m(m), content(n*m){}
	uint32_t r()const{return n;}
	uint32_t c()const{return m;}
	T& at(uint32_t x, uint32_t y){
		return content[x*m+y];
		// return content.at(x*m+y);
	}
	matrix operator+(matrix rhs)const{
		assert(n==rhs.n and m==rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++)
			rhs.at(i, j)=at(i, j)+rhs.at(i, j);
		return rhs;
	}
	matrix operator-(matrix rhs)const{
		assert(n==rhs.n and m==rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++)
			rhs.at(i, j)=at(i, j)-rhs.at(i, j);
		return rhs;
	}
	matrix dot(matrix rhs)const{
		assert(n==rhs.n and m==rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++)
			rhs.at(i, j)=at(i, j)*rhs.at(i, j);
		return rhs;
	}
	matrix operator*(const matrix& rhs)const{
		assert(m==rhs.n);
		matrix ret(n, rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++){
			for(uint32_t k=0; k<rhs.m; k++)
				ret.at(i, k)=ret.at(i, k)+content[i*m+j]*rhs.content.at(j*rhs.m+k);
		}
		return ret;
	}
	matrix& operator+=(const matrix& rhs){
		assert(n==rhs.n and m==rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++)
			at(i, j)=at(i, j)+rhs.at(i, j);
		return *this;
	}
	matrix& operator-=(const matrix& rhs){
		assert(n==rhs.n and m==rhs.m);
		for(uint32_t i=0; i<n; i++)for(uint32_t j=0; j<m; j++)
			at(i, j)=at(i, j)-rhs.at(i, j);
		return *this;
	}
	matrix& operator*=(const matrix& rhs){
		return *this=operator*(rhs);
	}
};
template<int32_t mod>
struct mint{
	int32_t a;
	mint(int32_t a=0):a(a){}
	mint operator+(mint rhs)const{int32_t d=a+rhs.a;return d<mod?d:d-mod;}
	mint operator-(mint rhs)const{int32_t d=a-rhs.a;return d<0?d+mod:d;}
	mint operator*(mint rhs)const{return (int64_t)a*rhs.a%mod;}
};