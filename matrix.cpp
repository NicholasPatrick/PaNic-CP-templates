#include <cstdio>
#include <queue>
#include <cstdarg>
#include <cassert>

template<typename T>
class matrix{
	std::vector<std::vector<T>> a;
public:
	matrix(){}
	matrix(int n, int m):a(n, std::vector<T>(m)){}
	matrix(int n, int m, T v):a(n, std::vector<T>(m, v)){}
	size_t n()const{
		return a.size();
	}
	size_t m()const{
		return a.empty()?0:a[0].size();
	}
	std::vector<T>& operator[](int index){
		return a[index];
	}
	std::vector<T>& at(int index){
		return a.at(index);
	}
	T& at(int x, int y){
		return a.at(x).at(y);
	}
	matrix operator+(matrix rhs)const{
		assert(n()==rhs.n() and m()==rhs.m());
		for(int i=0; i<n(); i++)for(int j=0; j<m(); j++)
			rhs[i][j]=a[i][j]+rhs[i][j];
		return rhs;
	}
	matrix operator-(matrix rhs)const{
		assert(n()==rhs.n() and m()==rhs.m());
		for(int i=0; i<n(); i++)for(int j=0; j<m(); j++)
			rhs[i][j]=a[i][j]-rhs[i][j];
		return rhs;
	}
	matrix dot(matrix rhs)const{
		assert(n()==rhs.n() and m()==rhs.m());
		for(int i=0; i<n(); i++)for(int j=0; j<m(); j++)
			rhs[i][j]=a[i][j]*rhs[i][j];
		return rhs;
	}
	matrix operator*(const matrix& rhs)const{
		/*
			Additional identity must exist
		*/
		assert(m()==rhs.n());
		matrix ret(n(), rhs.m());
		for(int i=0; i<n(); i++)for(int j=0; j<m(); j++){
			for(int k=0; k<rhs.m(); k++)
				ret[i][k]=ret[i][k]+a[i][j]*rhs.a[j][k];
		}
		return ret;
	}
};