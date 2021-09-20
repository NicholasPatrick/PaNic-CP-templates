#include <cstdint>

template <typename T>
T mulexp(T a, T b, uint32_t e){
	//a*b^e
	for(; e; e>>=1, b=b*b)
		if(e&1)a=a*b;
	return a;
}
template <typename T>
T expmul(T b, uint32_t e, T a){
	//b^e*a
	for(; e; e>>=1, b=b*b)
		if(e&1)a=b*a;
	return a;
}