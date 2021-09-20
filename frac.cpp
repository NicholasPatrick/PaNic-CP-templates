template <typename T>
class frac{
	T num, den;
	frac():num(0), den(1){}
	frac(T num):num(num), den(1){}
	frac(T num, T den):num(num), den(den){}
	frac operator+(frac rhs)const{
		if(rhs.den==den){
			rhs.num=num+rhs.num;
			return rhs;
		}
		rhs.num=rhs.den*num+rhs.num*den;
		rhs.den=den*rhs.den;
		return rhs;
	}
	frac operator-(frac rhs)const{
		if(rhs.den==den){
			rhs.num=num-rhs.num;
			return rhs;
		}
		rhs.num=rhs.den*num-rhs.num*den;
		rhs.den=den*rhs.den;
		return rhs;
	}
	frac operator*(frac rhs)const{
		if(rhs.num==den){
			rhs.num=num;
			return rhs;
		}
		if(rhs.den==num){
			rhs.den=den;
			return rhs;
		}
		rhs.num*=num;
		rhs.den*=den;
		return rhs;
	}
	frac operator/(frac rhs)const{
		//don't divide by 0
		swap(rhs.num, rhs.den);
		if(rhs.num==den){
			rhs.num=num;
			return rhs;
		}
		if(rhs.den==num){
			rhs.den=den;
			return rhs;
		}
		rhs.num*=num;
		rhs.den*=den;
		return rhs;
	}
	frac& operator+=(frac rhs){return *this=operator+(rhs);}
	frac& operator-=(frac rhs){return *this=operator-(rhs);}
	frac& operator*=(frac rhs){return *this=operator*(rhs);}
	frac& operator/=(frac rhs){return *this=operator/(rhs);}
	bool operator<(frac rhs)const{return num*rhs.den<rhs.num*den;}
	bool operator<=(frac rhs)const{return num*rhs.den<=rhs.num*den;}
	bool operator>(frac rhs)const{return num*rhs.den>rhs.num*den;}
	bool operator>=(frac rhs)const{return num*rhs.den>=rhs.num*den;}
	bool operator==(frac rhs)const{return num*rhs.den==rhs.num*den;}
	bool operator!=(frac rhs)const{return num*rhs.den!=rhs.num*den;}
};