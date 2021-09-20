#include <cstdint>

class m2611{
	//mod 2^61-1
	int64_t v;
public:
	static const int64_t mod=(1ll<<61)-1;
	m2611(int64_t v=0):v(v){}
	m2611& operator+=(m2611 rhs){v+=rhs.v;if(v>=mod)v-=mod;return *this;}
	m2611& operator-=(m2611 rhs){v-=rhs.v;if(v<0)v+=mod;return *this;}
	m2611& operator*=(m2611 rhs){return *this=operator*(rhs);}
	m2611 operator+(m2611 rhs)const{rhs.v+=v;return rhs.v<mod?rhs.v:rhs.v-mod;}
	m2611 operator-(m2611 rhs)const{rhs.v-=v;return rhs.v<=0?-rhs.v:mod-rhs.v;}
	m2611 operator*(m2611 rhs)const{
		int64_t x=(v&0x7fffffffu)*(rhs.v>>30)+((v>>31)*(rhs.v&0x3fffffffu)<<1);
		int64_t ret=(v&0x7fffffffu)*(rhs.v&0x3fffffffu)+(v>>31)*(rhs.v>>30)+(x>>31)+(x<<30&mod);
		ret=(ret&mod)+(ret>>61);
		return ret<mod?ret:ret-mod;
	}
	bool operator==(m2611 rhs)const{return v==rhs.v;}
	bool operator!=(m2611 rhs)const{return v!=rhs.v;}
	int64_t eval()const{return v;}
};