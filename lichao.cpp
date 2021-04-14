#include <cstdio>
#include <queue>
#include <cstdint>
#include <cassert>
#include <type_traits>
using namespace std;

template<typename T>
struct __int_lichao{
	struct line{
		T m, c;
		line(){};
		line(T m, T c):m(m), c(c){}
		T intersect(const line& rhs)const{
			T ret=(c-rhs.c)/(rhs.m-m);
			return ret*(rhs.m-m)==c-rhs.c?ret:ret-(rhs.c<c^m<rhs.m);
		}
		T eval(T x)const{
			return m*x+c;
		}
	};
	vector<T> xvalues;
	vector<line> lines;
	vector<int32_t> lineref;
	vector<uint32_t> children;
public:
	__int_lichao(){
		xvalues
	}
};
template<typename T>
struct __float_lichao{
public:
	__float_lichao(){}
};
template<typename T>
using lichao=conditional_t<is_integral_v<T>, __int_lichao<T>, __float_lichao<T>>;
int main(){
	lichao<long long> a;
	lichao<long long>::line x(10, -1);
	x.c=-x.c;
	printf("%lld\n", x.intersect(lichao<long long>::line(0, 0)));
}