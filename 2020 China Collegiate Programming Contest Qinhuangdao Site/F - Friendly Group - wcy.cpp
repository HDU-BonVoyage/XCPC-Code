#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=1e6+10;
int T,n,m,st[maxn<<1],to[maxn<<1],nt[maxn<<1],id[maxn<<1],topt,ans,nowp,nowd;
bool f[maxn],v[maxn];
inline void add(int x,int y,int z){to[++topt]=y; nt[topt]=st[x]; st[x]=topt; id[topt]=z;}
void dfs(int x)
{
	if (!v[x]) nowp++,v[x]=1;
	int p=st[x]; 
	while (p)
	{
		if (!f[id[p]]) {f[id[p]]=1; nowd++; dfs(to[p]);}
		p=nt[p];
	}
}
void solve()
{
	scanf("%d%d",&n,&m); topt=0; ans=0;
	for (int i=1;i<=n;i++) st[i]=0,v[i]=0;
	for (int i=1;i<=m;i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		add(x,y,i); add(y,x,i); f[i]=0;
 	}
 	for (int i=1;i<=n;i++)
 	if (!v[i])
 	{
 		nowd=0; nowp=0; dfs(i);
 		ans+=max(0,nowd-nowp);
	}
	printf("%d\n",ans);
	topt=0; ans=0;
	for (int i=1;i<=n;i++) st[i]=0,v[i]=0;
}
int main()
{
	scanf("%d",&T); int ca=0;
	while (T--) printf("Case #%d: ",++ca),solve();
return 0;
}
