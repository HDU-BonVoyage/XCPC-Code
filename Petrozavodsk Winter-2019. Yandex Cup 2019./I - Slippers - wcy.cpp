#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+10;
const int M = N*20;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow;
};
struct Dinic{
    int n,s,t,cur[N],d[N],head[N],tol;
    bool vis[N]; Edge edge[M];
    void init(int _n,int _s,int _t){
        n=_n; s=_s; t=_t; tol=0;
        for(int i=1;i<=n;++i) head[i]=-1;
    }
    void addedge(int u,int v,int c){
        edge[tol].to=v; edge[tol].cap=c; edge[tol].flow=0;
        edge[tol].next=head[u]; head[u]=tol++;
        edge[tol].to=u; edge[tol].cap=0; edge[tol].flow=0;
        edge[tol].next=head[v]; head[v]=tol++;
    }

    int que[N],front,tail;
    bool bfs(){
        for(int i=1;i<=n;++i) vis[i]=false;
        front=0; tail=-1;
        que[++tail]=s; vis[s]=true; d[s]=0;
        while(front<=tail){
            int x=que[front++];
            for(int i=head[x];~i;i=edge[i].next){
                Edge& e=edge[i];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=true; d[e.to]=d[x]+1;
                    que[++tail]=e.to;
                }
            }
        }
        return vis[t];
    }

    int dfs(int x,int a){
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int& i=cur[x];~i;i=edge[i].next){
            Edge& e=edge[i];
            if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f; edge[i^1].flow-=f;
                flow+=f; a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }

    int Maxflow(){
        int flow=0;
        while(bfs()){
            for(int i=1;i<=n;++i) cur[i]=head[i];
            flow+=dfs(s,INF);
        }
        return flow;
    }
}dinic;
char s[110][110],d[110][110]; int dd[110][110]; int n,m,op,ans;
char read_char(){
    char ch=getchar();
    while(ch!='>'&&ch!='<'&&ch!='^'&&ch!='v'&&ch!='L'&&ch!='R') ch=getchar();
    return ch;
}
int getpoint(int x,int y){
    return (x-1)*m+y;
}
int main(){
    scanf("%d %d",&n,&m); dinic.init(n*m+2,n*m+1,n*m+2);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            s[i][j]=read_char(); d[i][j]=read_char();
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(d[i][j]=='^') dd[i][j]=0;
            else if(d[i][j]=='<') dd[i][j]=1;
            else if(d[i][j]=='v') dd[i][j]=2;
            else dd[i][j]=3;
            if((i+j)&1){
                dinic.addedge(n*m+1,getpoint(i,j),1);
                if(i>1&&s[i][j]!=s[i-1][j]) dinic.addedge(getpoint(i,j),getpoint(i-1,j),1);
                if(i<n&&s[i][j]!=s[i+1][j]) dinic.addedge(getpoint(i,j),getpoint(i+1,j),1);
                if(j>1&&s[i][j]!=s[i][j-1]) dinic.addedge(getpoint(i,j),getpoint(i,j-1),1);
                if(j<m&&s[i][j]!=s[i][j+1]) dinic.addedge(getpoint(i,j),getpoint(i,j+1),1);
            }else dinic.addedge(getpoint(i,j),n*m+2,1);
        }
    }
    ans=dinic.Maxflow();
    for(int i=1;i<=n*m;++i){
        int x=i/m+(i%m!=0),y=i%m+(i%m==0?m:0);
        if(((x+y)&1)==0) continue;
        for(int o=dinic.head[i];~o;o=dinic.edge[o].next){
            if(dinic.edge[o].cap==dinic.edge[o].flow&&dinic.edge[o].cap==1){
                int j=dinic.edge[o].to;
                //if(j>n*m) continue;
                int a=j/m+(j%m!=0),b=j%m+(j%m==0?m:0);
                //printf("%d %d - %d %d\n",x,y,a,b);
                if(x==a){
                    op+=dd[x][y]; op+=dd[a][b];
                }else{
                    op+=dd[x][y]+3; op+=dd[a][b]+3;
                }
            }
        }
    }
    if(ans*2==n*m&&op%4!=0) ans--;
    printf("%d\n",ans);
}
