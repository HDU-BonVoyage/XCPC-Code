#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+10;
struct Edge{
	int u,v,w;
	bool operator < (const Edge &e) const{
		return w<e.w;
	}
}e[N];
int fa[N],siz[N],n,m; ll ans;
int get(int x){
	if(fa[x]==x) return x;
	else return fa[x]=get(fa[x]);
}
int unite(int x,int y,int w){
	x=get(x); y=get(y);
	if(x==y) return 0;
	ans+=1ll*w*siz[x]*siz[y];
	fa[y]=x; siz[x]+=siz[y];
	return x;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
		scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+1+m);
	for(int i=1;i<=n;++i) fa[i]=i,siz[i]=1;
	for(int i=m,j=m,op;i>=1;i=j){
		while(j>=1&&e[j].w==e[i].w){
			if(get(e[j].u)==get(e[j].v)){
				ans=-1; break;
			}
			--j;
		}
		if(ans==-1) break;
		for(int k=j+1;k<=i;++k)
			unite(e[k].u,e[k].v,e[k].w);
	}
	int sz=0;
	if(ans!=-1){
		for(int i=1;i<=n;++i){
			if(get(i)==i){
				ans+=1ll*siz[i]*sz;
				sz+=siz[i];
			}
		}	
	}
	printf("%lld\n",ans);
}
