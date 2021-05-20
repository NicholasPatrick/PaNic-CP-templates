#include <cstdio>
#include <queue>

const int maxn=1e5;
std::vector<int> adjLis[maxn];
int par[maxn], jump[maxn], depth[maxn];
void dfs1(int x){
	int j=jump[x];
	for(int y : adjLis[x]){
		if(y==par[x])
			continue;
		jump[y]=depth[jump[j]]+depth[x]==depth[j]<<1?jump[j]:x;
		par[y]=x;
		depth[y]=depth[x]+1;
		dfs1(y);
	}
}
int lca(int x, int y){
	if(depth[x]<depth[y])
		std::swap(x, y);
	while(depth[x]>depth[y]){
		if(depth[jump[x]]>depth[y])
			x=jump[x];
		else
			x=par[y];
	}
	if(x==y)
		return x;
	while(par[x]!=par[y]){
		if(jump[x]!=jump[y]){
			x=jump[x];
			y=jump[y];
		}else{
			x=par[x];
			y=par[y];
		}
	}
	return par[x];
}
int lca(int x, int y, int z){
	int a=lca(x, y), b=lca(y, z), c=lca(x, z);
	if(depth[a]>=depth[b]){
		if(depth[a]>=depth[c])
			return a;
		return c;
	}
	if(depth[b]>=depth[c])
		return b;
	return c;
}
int la(int x, int y){
	while(y){
		if(depth[jump[x]]-depth[x]<=y){
			y-=depth[jump[x]]-depth[x];
			x=jump[x];
		}else{
			y--;
			x=par[x];
		}
	}
	return x;
}