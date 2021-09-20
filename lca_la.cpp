#include <cstdint>
#include <queue>

const uint32_t maxn=1e5;
std::vector<uint32_t> adjLis[maxn];
uint32_t par[maxn], jump[maxn], depth[maxn];
void dfs1(uint32_t x){
	uint32_t j=jump[x];
	for(uint32_t y : adjLis[x]){
		if(y==par[x])
			continue;
		jump[y]=depth[jump[j]]+depth[x]==depth[j]<<1?jump[j]:x;
		par[y]=x;
		depth[y]=depth[x]+1;
		dfs1(y);
	}
}
uint32_t lca(uint32_t x, uint32_t y){
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
uint32_t lca(uint32_t x, uint32_t y, uint32_t z){
	uint32_t a=lca(x, y), b=lca(y, z), c=lca(x, z);
	if(depth[a]>=depth[b]){
		if(depth[a]>=depth[c])
			return a;
		return c;
	}
	if(depth[b]>=depth[c])
		return b;
	return c;
}
uint32_t la(uint32_t x, uint32_t y){
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
uint32_t la(uint32_t x, uint32_t y, uint32_t r){
	uint32_t l=lca(x, r);
	if(depth[x]-depth[l]<=y)
		return la(x, y);
	return la(r, y-depth[x]+depth[l]);
}