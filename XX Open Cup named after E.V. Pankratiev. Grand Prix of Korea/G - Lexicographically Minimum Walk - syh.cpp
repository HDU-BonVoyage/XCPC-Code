#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#define pb push_back
using namespace std;
const int inf=1e9+10;
const int maxn=1e6+10;
const int lim=1e6+5;
int n,m,s,t,st[maxn],to[maxn],nt[maxn],topt,w[maxn],mi[maxn],ans[maxn],cnt,g[maxn],tt[maxn];
struct da{int x,y,z;}q[maxn];
bool f[maxn];
void add(int x,int y,int z){to[++topt]=y; nt[topt]=st[x]; st[x]=topt; w[topt]=z;}
void dfs1(int x)
{
	f[x]=1; int p=st[x];
	while (p)
	{
		if (!f[to[p]]) dfs1(to[p]);
		p=nt[p];
	}
}
void dfs2(int x)
{
	if (cnt>=lim) return;
	if (x==t) return;
	ans[++cnt]=mi[x]; dfs2(g[x]); 
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for (int i=1;i<=n;i++) mi[i]=inf;
	for (int i=1;i<=m;i++) scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z),add(q[i].y,q[i].x,q[i].z);
	dfs1(t); if (!f[s]) {printf("IMPOSSIBLE\n"); return 0;}
	for (int i=1;i<=m;i++) if (f[q[i].x] && f[q[i].y]) mi[q[i].x]=min(mi[q[i].x],q[i].z);
	for (int i=1;i<=m;i++) if (f[q[i].x] && f[q[i].y] && mi[q[i].x]==q[i].z) g[q[i].x]=q[i].y;
	dfs2(s); if (cnt>1000000) {printf("TOO LONG\n"); return 0;}
	for (int i=1;i<=cnt;i++) printf("%d%c",ans[i],(i==cnt?'\n':' '));
return 0;
}
