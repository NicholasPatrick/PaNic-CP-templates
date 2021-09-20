#include <cstdio>
#include <queue>
#include <bitset>

const int maxn=1e5;
std::vector<int> adjLis[maxn];
std::bitset<maxn> mark;
int sz[maxn];
int getsz(int x, int p=-1){
	sz[x]=1;
	for(int y : adjLis[x]){
		if(y==p or mark[y])
			continue;
		sz[x]+=getsz(y);
	}
	return sz[x];
}
int getcent(int x, int ts){
	for(int y : adjLis[x]){
		if(sz[y]>sz[x] or mark[y])
			continue;
		if(sz[y]>ts>>1)
			return getcent(y, ts);
	}
	return x;
}
void centdecomp(int x=0){
	mark[x=getcent(x, getsz(x))]=true;
	/*
		do stuff here
	*/
	for(int y : adjLis[x]){
		if(mark[y])
			continue;
		//centroid parent of y is x
		centdecomp(y);
	}
}