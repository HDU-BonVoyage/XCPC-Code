#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pr;
const int N = 5e5+10;
const int M = 2e6+10;
const ll INF = 1e18;
const int inf = 0x3f3f3f3f;
struct MCMF{
    struct Edge{
        int to,next,cap,flow; ll cost;
    }e[M];
    int head[N],n,m;
    int pre[N]; ll dis[N],het[N];
    bool vis[M];
    void init(int _n){
        n=_n; m=0;
        for(int i=1;i<=n;++i) head[i]=-1,het[i]=0;
    }
    void addedge(int u,int v,int cap,ll cost){
        e[m].to=v; e[m].cap=cap;
        e[m].cost=cost; e[m].flow=0;
        e[m].next=head[u]; head[u]=m++;
        e[m].to=u; e[m].cap=0;
        e[m].cost=-cost; e[m].flow=0;
        e[m].next=head[v]; head[v]=m++;
    }
    bool spfa(int s,int t){
        queue<int> Q;
        for(int i=1;i<=n;++i){
            dis[i]=INF; vis[i]=false; pre[i]=-1;
        }
        dis[s]=0; vis[s]=true;
        Q.push(s);
        while (!Q.empty()){
            int u = Q.front(); Q.pop();
            vis[u]=false;
            for(int i=head[u];~i;i=e[i].next){
                int v=e[i].to;
                if(e[i].cap>e[i].flow&&dis[v]>dis[u]+e[i].cost){
                    dis[v]=dis[u]+e[i].cost;
                    pre[v]=i;
                    if(!vis[v]){
                        vis[v]=true;
                        Q.push(v);
                    }
                }
            }
        }
        return pre[t]!=-1;
    }
    bool dijk(int s,int t){
    	priority_queue<pr,vector<pr>,greater<pr> > Q;
    	for(int i=1;i<=n;++i){
            dis[i]=INF; pre[i]=-1;
        }
        dis[s]=0;
        Q.push(make_pair(0,s));
        while(!Q.empty()){
        	pr now=Q.top(); Q.pop();
        	if(dis[now.second]<now.first) continue;
        	int u=now.second;
        	for(int i=head[u];~i;i=e[i].next){
        		int v=e[i].to;
        		if(e[i].cap>e[i].flow&&dis[v]>dis[u]+e[i].cost){
        			//if(e[i].cost<0) printf("lapls %lld\n",e[i].cost);
					//assert(e[i].cost>=0);
					dis[v]=dis[u]+e[i].cost;
					pre[v]=i;
                    Q.push(make_pair(dis[v],v));
				}
			}
		}
    	return pre[t]!=-1;
	}
    int minCostMaxflow(int s,int t,ll &cost){
        int flow=0; cost=0;
        for(int u=1;u<=n;++u) dis[u]=0;
        for(int u=1;u<=n;++u){
        	for(int i=head[u];~i;i=e[i].next){
        		if(e[i].cap<=e[i].flow) continue;
        		dis[e[i].to]=min(dis[e[i].to],dis[u]+e[i].cost);
			}
		}
		for(int u=1;u<=n;++u){
            for(int i=head[u];~i;i=e[i].next){
            	e[i].cost+=dis[u]-dis[e[i].to];
			}
			het[u]+=dis[u];
		}
        while(dijk(s,t)){
            int Min=inf;
            for(int i=pre[t];i!=-1;i=pre[e[i^1].to]){
                if(Min>e[i].cap-e[i].flow)
                    Min=e[i].cap-e[i].flow;
            }
            for(int i=pre[t];i!=-1;i=pre[e[i^1].to]){
                e[i].flow+=Min;
                e[i^1].flow-=Min;
                cost+=e[i].cost*Min;
			}
            flow+=Min; cost+=het[t]*Min;
			for(int i=1;i<=n;++i) het[i]+=dis[i];
			for(int u=1;u<=n;++u){
            	for(int i=head[u];~i;i=e[i].next){
            		e[i].cost+=dis[u]-dis[e[i].to];
				}
			}
        }
        return flow;
    }
}mcmf;
int n,m;
struct Seg{
	int l,r; ll w;
}a[N]; ll ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d %d %lld",&a[i].l,&a[i].r,&a[i].w);
		m=max(m,a[i].r+1);
	}
	mcmf.init(m+1);
	for(int i=1;i<=m;++i) mcmf.addedge(i,i+1,2,0);
	for(int i=1;i<=n;++i) mcmf.addedge(a[i].l,a[i].r+1,1,-a[i].w);
	mcmf.minCostMaxflow(1,m+1,ans);
	printf("%lld\n",-ans);
}
