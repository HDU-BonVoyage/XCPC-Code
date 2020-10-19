#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct Edge{
    int u,v;
}e[N];
vector<int> g[N],p[N],q[N];
int n,m,a,b;
bool check(int k){
    for(int i=1;i<=n;++i) p[i].clear(),q[i].clear();
    for(int i:g[a]){
        if(i>k) continue;
        int u=e[i].u^e[i].v^a;
        if(u==b) continue;
        for(int j:g[u]){
            if(j>k) continue;
            int v=e[j].u^e[j].v^u;
            if(v==a||v==b) continue;
            if(p[v].size()<3){
                p[v].push_back(u);
                //printf("%d -> %d\n",u,v);
            }
        }
    }
    for(int i:g[b]){
        if(i>k) continue;
        int u=e[i].u^e[i].v^b;
        if(u==a) continue;
        for(int j:g[u]){
            if(j>k) continue;
            int v=e[j].u^e[j].v^u;
            if(v==a||v==b) continue;
            if(q[v].size()<3){
                q[v].push_back(u);
                //printf("%d -> %d\n",v,u);
            }
        }
    }
    for(int i=1;i<=k;++i){
        if(e[i].u==a||e[i].u==b||e[i].v==a||e[i].v==b) continue;
        for(int u:p[e[i].u]){
            for(int v:q[e[i].v]){
                if(v!=e[i].u&&v!=u&&u!=e[i].v) return true;
            }
        }
        for(int v:p[e[i].v]){
            for(int u:q[e[i].u]){
                if(u!=e[i].v&&u!=v&&v!=e[i].u) return true;
            }
        }
    }
    return false;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;++i){
        scanf("%d %d",&e[i].u,&e[i].v);
        g[e[i].u].push_back(i);
        g[e[i].v].push_back(i);
    }
    scanf("%d %d",&a,&b);
    int l=0,r=m+1,mid;
    while(l+1<r){
        mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    if(r==m+1) printf("-1\n");
    else printf("%d\n",r);
}
