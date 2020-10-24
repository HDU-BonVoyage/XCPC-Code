#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int dep[N],mn[N],mx[N],fa[N],n,ans;
bool cmp(int x,int y){
	return mx[x]<mx[y];
}
vector<int> g[N];
int dfs(int u){
	int rs=0; mn[u]=N; mx[u]=dep[u];
	if(g[u].size()==0) rs=1;
	for(auto v:g[u]){
		dep[v]=dep[u]+1; rs+=dfs(v);
		mx[u]=max(mx[u],mx[v]);
	}
	sort(g[u].begin(),g[u].end(),cmp);
	for(int i=0,v,vv;i+1<(int)g[u].size();++i){
		v=g[u][i]; vv=g[u][i+1];
		if(mx[v]-dep[u]<dep[u]){
			ans+=mx[v]-dep[u]; --rs;
		}
	}
	if(u!=1) ans+=rs; return rs;
}
int main(){
	int T,cas=0; scanf("%d",&T);
	while(T--){ ++cas;
		scanf("%d",&n); ans=0;
		for(int i=2;i<=n;++i) scanf("%d",&fa[i]);
		for(int i=2;i<=n;++i) g[fa[i]].push_back(i);
		dfs(1); printf("Case #%d: %d\n",cas,ans);
		for(int i=1;i<=n;++i) g[i].clear();
	}
}
