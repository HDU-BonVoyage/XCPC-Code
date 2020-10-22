#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e15;
typedef pair<int,int> pii;
const int N = 510;
ll d[N][N],g[N][N];
int rk[N][N],n,m;
void floyd(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) d[i][j]=g[i][j];
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
void karivhakimi(int n,int &s1,int &s2,double &d1,double &d2){
	floyd();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) rk[i][j]=j;
		sort(rk[i]+1,rk[i]+1+n,[&](int a,int b){return d[i][a]<d[i][b]; });
	}
	ll ret=INF;
	s1=s2=-1; d1=d2=0;
	for(int u=1;u<=n;++u){
		if(d[u][rk[u][n]]*2<ret){
			ret=d[u][rk[u][n]]*2;
			s1=s2=u; d1=d2=0;
		}
		for(int v=1;v<=n;++v){
			if(g[u][v]==INF) continue;
			for(int k=n,i=n-1;i>=1;--i){
				if(d[v][rk[u][i]]>d[v][rk[u][k]]){
					ll tmp=d[u][rk[u][i]]+d[v][rk[u][k]]+g[u][v];
					if(tmp<ret){
						ret=tmp;
						s1=u,s2=v;
						d1=0.5*tmp-d[u][rk[u][i]];
						d2=g[u][v]-d1;
					}
					k=i;
				}
			}
		}
	}
}
double dis[N]; bool vis[N];
int u[N],v[N],fa[N];
void solve(){
	int s1,s2,m=0; double d1,d2;
	karivhakimi(n,s1,s2,d1,d2);
	for(int i=1;i<=n;++i) dis[i]=INF;
	dis[s1]=d1; dis[s2]=d2;
	if(s1!=s2){
		++m; u[m]=s1,v[m]=s2;
	}
	while(1){
		int u=-1;
		for(int i=1;i<=n;++i){
			if(vis[i]) continue;
			if(u==-1||dis[u]>dis[i]) u=i;
		}
		if(u==-1) break; vis[u]=true;
		for(int v=1;v<=n;++v){
			if(dis[v]>dis[u]+g[u][v]){
				fa[v]=u;
				dis[v]=dis[u]+g[u][v];
			}
		}
	}
	d1=d2=0;
	for(int i=1;i<=n;++i){
		if(dis[i]>d1) swap(d1,dis[i]);
		if(dis[i]>d2) swap(d2,dis[i]);
	}
	printf("%lld\n",(long long)(d1+d2+0.5));
	if(s1!=s2) printf("%d %d\n",s1,s2);
	for(int i=1;i<=n;++i)
		if(fa[i]) printf("%d %d\n",i,fa[i]);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) g[i][j]=i==j?0:INF;
	for(int i=1,u,v,w;i<=m;++i){
		scanf("%d %d %d",&u,&v,&w);
		g[u][v]=g[v][u]=w;
	}
	solve();
}
