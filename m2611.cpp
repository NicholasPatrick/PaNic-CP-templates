class m2611{
	long long v;
public:
	static const long long mod=(1ll<<61)-1;
	m2611(long long v=0):v(v){}
	m2611 operator+(m2611 rhs)const{rhs.v+=v;return rhs.v<mod?rhs.v:rhs.v-mod;}
	m2611 operator-(m2611 rhs)const{rhs.v-=v;return rhs.v<=0?-rhs.v:mod-rhs.v;}
	m2611 operator*(m2611 rhs)const{
		long long x=(v&0x7fffffffu)*(rhs.v>>30)+((v>>31)*(rhs.v&0x3fffffffu)<<1);
		long long ret=(v&0x7fffffffu)*(rhs.v&0x3fffffffu)+(v>>31)*(rhs.v>>30)+(x>>31)+(x<<30&mod);
		ret=(ret&mod)+(ret>>61);
		return ret<mod?ret:ret-mod;
	}
	bool operator==(m2611 rhs)const{return v==rhs.v;}
	bool operator!=(m2611 rhs)const{return v!=rhs.v;}
	long long eval()const{return v;}
};