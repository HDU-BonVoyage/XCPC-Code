#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int N = 250010;
const int D = 19;
struct Edge{
	int to; ll w;
	Edge(int _to,ll _w){
		to=_to; w=_w;
	}
};
int mx[N],siz[N],tot,rt,n; bool vis[N];
vector<Edge> g[N],t[N],nt[N];
vector<int> comp[N];
int l[N],r[N],lg[N<<1],rmq[D][N<<1],idx; ll dep[N];
void getroot(int u,int fa){
	siz[u]=1; mx[u]=0;
	for(auto e:g[u]){
		int v=e.to;
		if(v==fa||vis[v]) continue;
		getroot(v,u); siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],tot-siz[u]);
	if(!rt||mx[rt]>mx[u]) rt=u;
}
void getsiz(int p,int u,int fa){
	comp[p].push_back(u); siz[u]=1;
	for(auto e:g[u]){
		int v=e.to;
		if(v==fa||vis[v]) continue;
		getsiz(p,v,u); siz[u]+=siz[v];
	}
}
ll a[N]; int tag[N];
void getdis(int u,int fa){
	for(auto e:g[u]){
		int v=e.to;
		if(!tag[v]||v==fa) continue;
		a[v]=a[u]+e.w; getdis(v,u);
	}
}
pair<int,int> pr[N*2*D];
int cnt[N<<1];
void SORT(){
	for(int i=1;i<=idx;++i) cnt[i]=0;
	for(int i=1;i<=n;++i) for(auto u:comp[i]) ++cnt[l[u]];
	for(int i=1;i<=idx;++i) cnt[i]+=cnt[i-1];
	int tot=cnt[idx];
	for(int i=1;i<=n;++i){
		for(auto u:comp[i]) pr[--cnt[l[u]]]=make_pair(i,u);
		comp[i].clear();
	}
	for(int i=0;i<tot;++i) comp[pr[i].first].push_back(pr[i].second);
}
void divide(int u){
	if(tot==1) return;
	rt=0; getroot(u,u); u=rt;
	vis[u]=true; getsiz(u,u,u);
	for(auto e:g[u]){
		int v=e.to; if(vis[v]) continue;
		tot=siz[v]; divide(v);
	}
}
void dfs1(int u,int fa){
	l[u]=++idx; rmq[0][idx]=u;
	for(auto e:t[u]){
		int v=e.to; if(v==fa) continue;
		dep[v]=dep[u]+e.w; dfs1(v,u);
		rmq[0][++idx]=u;
	}
	r[u]=idx;
}
ll ans[N],dp[N];
void dfs2(int u,int fa){
	dp[u]=a[u];
	for(auto e:nt[u]){
		int v=e.to; if(v==fa) continue;
		dfs2(v,u);
		dp[u]=min(dp[u],dp[v]+e.w);
	}
}
void dfs3(int u,int fa,ll op){
	ll p=op,q=INF; int o=-1;
	for(auto e:nt[u]){
		int v=e.to; if(v==fa) continue;
		if(dp[v]+e.w<p){
			q=p; p=dp[v]+e.w; o=v;
		}else if(dp[v]+e.w<q) q=dp[v]+e.w;
	}
	ans[u]=min(ans[u],p+a[u]);
	if(a[u]<p) q=p,p=a[u],o=u;
	else if(a[u]<q) q=a[u];
	for(auto e:nt[u]){
		int v=e.to; if(v==fa) continue;
		dfs3(v,u,v==o?(q+e.w):(p+e.w));
	}
}
void initrmq(){
	lg[0]=-1; for(int i=1;i<=idx;++i) lg[i]=i&(i-1)?lg[i-1]:lg[i-1]+1;
	for(int i=1;i<D;++i) for(int j=1;j+(1<<i)-1<=idx;++j)
		rmq[i][j]=dep[rmq[i-1][j]]<dep[rmq[i-1][j+(1<<(i-1))]]?rmq[i-1][j]:rmq[i-1][j+(1<<(i-1))];
}
int lca(int u,int v){
	u=l[u]; v=l[v]; if(u>v) swap(u,v);
	int o=lg[v-u+1],a,b;
	a=rmq[o][u],b=rmq[o][v-(1<<o)+1];
	return dep[a]<dep[b]?a:b;
}
void solve(vector<int> &v,int rt){
	if((int)v.size()==0) return ;
	auto ed=unique(v.begin(),v.end()); v.erase(ed,v.end());
	for(auto o:v) tag[o]=1,a[o]=INF;
	a[rt]=0; getdis(rt,rt);
	stack<int> st;
	for(auto o:v){
		while(!st.empty()&&r[st.top()]<l[o]) st.pop(); 
		if(!st.empty())
			nt[st.top()].push_back(Edge(o,dep[o]-dep[st.top()]));
		st.push(o);
	}
	dfs2(v[0],v[0]); dfs3(v[0],v[0],INF);
	for(auto o:v) tag[o]=0,nt[o].clear();
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;++i){
		scanf("%d %d %d",&u,&v,&w);
		g[u].push_back(Edge(v,w));
		g[v].push_back(Edge(u,w));
	}
	for(int i=1,u,v,w;i<n;++i){
		scanf("%d %d %d",&u,&v,&w);
		t[u].push_back(Edge(v,w));
		t[v].push_back(Edge(u,w));
	}
	dfs1(1,1); initrmq();
	tot=n; divide(1); SORT();
	for(int i=1,s;i<=n;++i){
		s=comp[i].size();
		for(int j=0;j+1<s;++j)
			comp[i].push_back(lca(comp[i][j],comp[i][j+1]));
	}
	SORT();
	for(int i=1;i<=n;++i) ans[i]=INF;
	for(int i=1;i<=n;++i) solve(comp[i],i);
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
}
