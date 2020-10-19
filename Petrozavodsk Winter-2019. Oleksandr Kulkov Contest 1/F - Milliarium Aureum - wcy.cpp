#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
struct Edge{
    int u,v,w,t;
    bool operator < (const Edge &e) const{
        if(w!=e.w) return w>e.w;
        return t>e.t;
    }
}e[N];
int fa1[N],fa2[N],op[N],n,m;
vector<int> g[N];
int get1(int x){
    if(fa1[x]==x) return x;
    else return fa1[x]=get1(fa1[x]);
}
int get2(int x){
    if(fa2[x]==x) return x;
    else return fa2[x]=get2(fa2[x]);
}
void unite1(int u,int v){
    fa1[get1(u)]=get1(v);
}
void unite2(int u,int v){
    u=get2(u); v=get2(v);
    if(u==v) return ;
    if(op[u]) fa2[v]=u;
    else fa2[u]=v;
    if(op[u]&&op[v]){
        g[u].push_back(v);
        g[v].push_back(u);
    }
}
void dfs(int u,int f){
    //printf("%d %d\n",u,f);
    op[u]=0;
    for(auto v:g[u]) if(v!=f) dfs(v,u);
    g[u].clear();
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) fa1[i]=fa2[i]=i,op[i]=1;
    for(int i=1;i<=m;++i){
        scanf("%d %d %d %d",&e[i].t,&e[i].u,&e[i].v,&e[i].w);
    }
    sort(e+1,e+1+m);
    for(int i=1,j=1;i<=m;i=j){
        while(j<=m&&e[j].w==e[i].w) ++j;
        for(int k=i;k<j;++k){
            if(e[k].t&&get2(e[k].u)==get2(e[k].v)){
                dfs(get2(e[k].u),-1);
            }
        }
        for(int k=i;k<j;++k){
            if(e[k].t){
                unite1(e[k].u,e[k].v);
                unite2(e[k].u,e[k].v);
            }else unite2(e[k].u,e[k].v);
        }
        for(int k=i;k<j;++k){
            if(!e[k].t){
                if(get1(e[k].u)!=get1(e[k].v)){
                    dfs(get2(e[k].u),-1);
                    dfs(get2(e[k].v),-1);
                }
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=n;++i) if(op[i]) ++cnt;
    printf("%d\n",cnt);
    for(int i=1;i<=n;++i) if(op[i]) printf("%d ",i);
}
