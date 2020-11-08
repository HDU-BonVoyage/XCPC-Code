#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
const int D = 19;
struct Bit{
	ll f[N],g[N]; int n;
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;++i) f[i]=g[i]=0;
	}
	void add(int x,int v){
		ll vv=1ll*x*v;
		for(int i=x;i<=n;i+=i&-i){
			f[i]+=v; g[i]+=vv;
		}
	}
	ll sum(int x){
		ll rs=0;
		for(int i=x;i;i-=i&-i){
			rs+=f[i]*(x+1)-g[i];
		}
		return rs;
	}
}bit;
int l[N],r[N],rk[N],siz[N],son[N],top[N],fa[N][D],n,q,idx;
ll tot;
vector<int> g[N];
void dfs1(int u,int f){
	fa[u][0]=f; siz[u]=1; son[u]=0;
	for(int i=1;i<D;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1]; 
	for(auto v:g[u]){
		if(v==f) continue;
		dfs1(v,u); siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v; 
	}
}
void dfs2(int u,int f,int t){
	l[u]=++idx; rk[idx]=u; top[u]=t;
	if(son[u]) dfs2(son[u],u,t);
	for(auto v:g[u]){
		if(v==f||v==son[u]) continue;
		dfs2(v,u,v);
	}
	r[u]=idx;
}
void update1(int u,int x){
	bit.add(l[u],x);
	bit.add(r[u]+1,-x);
	tot+=r[u]+1-l[u];
}
void update2(int u,int v,int x){
	while(top[u]!=top[v]){
		if(l[u]<l[v]){
			bit.add(l[top[v]],x);
			bit.add(l[v]+1,-x);
			tot+=l[v]+1-l[top[v]];
			v=fa[top[v]][0];
		}else{
			bit.add(l[top[u]],x);
			bit.add(l[u]+1,-x);
			tot+=l[u]+1-l[top[u]];
			u=fa[top[u]][0];
		}
	}
	if(l[u]>l[v]) swap(u,v);
	bit.add(l[u],x);
	bit.add(l[v]+1,-x);
	tot+=l[v]+1-l[u];
}
int query(){
	int ll=0,rr=n,mm;
	while(ll+1<rr){
		mm=(ll+rr)>>1;
		if(bit.sum(mm)>tot/2) rr=mm;
		else ll=mm;
	}
	int x=rk[rr];
	if(bit.sum(r[x])-bit.sum(l[x]-1)>tot/2) return x;
	for(int i=D-1;i>=0;--i){
		if(bit.sum(r[fa[x][i]])-bit.sum(l[fa[x][i]]-1)<=tot/2){
			x=fa[x][i];
		}
	}
	return fa[x][0];
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;++i){
		scanf("%d %d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,1); dfs2(1,1,1); bit.init(n);
	scanf("%d",&q);
	for(int i=1,op,u,v;i<=q;++i){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&u);
			update1(u,1);
		}else if(op==2){
			scanf("%d %d",&u,&v);
			update2(u,v,1);
		}
		printf("%d\n",query());
	}
}

