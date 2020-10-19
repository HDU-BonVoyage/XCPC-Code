#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int l[N],r[N],u[N],d[N]; 
int ll[N][N],rr[N][N],uu[N][N],dd[N][N],n,m;
char s[N][N];
void modify(int x,int y){
	if(s[x][y]=='#') s[x][y]='.';
	else s[x][y]='#';
	for(int j=y;j<=m;++j){
		if(s[x][j]=='#') ll[x][j]=ll[x][j-1]+1;
		else ll[x][j]=0;
	}
	for(int j=y;j>=1;--j){
		if(s[x][j]=='#') rr[x][j]=rr[x][j+1]+1;
		else rr[x][j]=0;
	}
	for(int i=x;i<=n;++i){
		if(s[i][y]=='#') uu[i][y]=uu[i-1][y]+1;
		else uu[i][y]=0;
	}
	for(int i=x;i>=1;--i){
		if(s[i][y]=='#') dd[i][y]=dd[i+1][y]+1;
		else dd[i][y]=0;
	}
}
int get(int *fa,int x){
	if(fa[x]==x) return x;
	else return fa[x]=get(fa,fa[x]);
}
vector<int> orz[N];
int query(int x,int y){
	int rs=0,xx,yy,p1,p2,q1,q2;
	for(int i=0;i<=n+1;++i) u[i]=d[i]=i;
	for(int i=0;i<=m;++i) orz[i].clear();
	for(int i=1;i<=n;++i) orz[ll[i][y]].push_back(i);
	for(int j=y;j>=1;--j){
		for(auto o:orz[y-j]) u[o]=u[o-1],d[o]=d[o+1]; 
		xx=x; yy=j;
		if(s[xx][yy]=='.') continue;
		p1=min(uu[xx][yy],uu[x][y]);
		p2=min(dd[xx][yy],dd[x][y]);
		q1=get(d,x-p1+1);
		q2=get(u,x+p2-1);
		//printf("que %d %d %d %d %d\n",j,p1,p2,q1,q2);
		if(q1>x||q2<x) continue;
		rs=max(rs,(q2-q1+1)*(y-j+1));
	}
	
	for(int i=0;i<=n+1;++i) u[i]=d[i]=i;
	for(int i=0;i<=m;++i) orz[i].clear();
	for(int i=1;i<=n;++i) orz[rr[i][y]].push_back(i);
	for(int j=y;j<=m;++j){
		for(auto o:orz[j-y]) u[o]=u[o-1],d[o]=d[o+1]; 
		xx=x; yy=j;
		if(s[xx][yy]=='.') continue;
		p1=min(uu[xx][yy],uu[x][y]);
		p2=min(dd[xx][yy],dd[x][y]);
		q1=get(d,x-p1+1);
		q2=get(u,x+p2-1);
		if(q1>x||q2<x) continue;
		rs=max(rs,(q2-q1+1)*(j-y+1));
	}
	
	for(int i=0;i<=m+1;++i) l[i]=r[i]=i;
	for(int i=0;i<=n;++i) orz[i].clear();
	for(int i=1;i<=m;++i) orz[uu[x][i]].push_back(i);
	for(int i=x;i>=1;--i){
		for(auto o:orz[x-i]) l[o]=l[o-1],r[o]=r[o+1]; 
		xx=i; yy=y;
		if(s[xx][yy]=='.') continue;
		p1=min(ll[xx][yy],ll[x][y]);
		p2=min(rr[xx][yy],rr[x][y]);
		q1=get(r,y-p1+1);
		q2=get(l,y+p2-1);
		if(q1>y||q2<y) continue;
		rs=max(rs,(q2-q1+1)*(x-i+1));
	}
	
	for(int i=0;i<=m+1;++i) l[i]=r[i]=i;
	for(int i=0;i<=n;++i) orz[i].clear();
	for(int i=1;i<=m;++i) orz[dd[x][i]].push_back(i);
	for(int i=x;i<=n;++i){
		for(auto o:orz[i-x]) l[o]=l[o-1],r[o]=r[o+1]; 
		xx=i; yy=y;
		if(s[xx][yy]=='.') continue;
		p1=min(ll[xx][yy],ll[x][y]);
		p2=min(rr[xx][yy],rr[x][y]);
		q1=get(r,y-p1+1);
		q2=get(l,y+p2-1);
		if(q1>y||q2<y) continue;
		rs=max(rs,(q2-q1+1)*(i-x+1));
	}
	
	return rs;
}
int T,cas,q,op,x,y;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&q);
		for(int i=1;i<=n;++i) scanf("%s",s[i]+1);
		for(int i=0;i<=n+1;++i){
			for(int j=0;j<=m+1;++j){
				ll[i][j]=rr[i][j]=uu[i][j]=dd[i][j]=0;
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(s[i][j]=='#'){
					ll[i][j]=ll[i][j-1]+1;
					uu[i][j]=uu[i-1][j]+1;
				}
			}
		}
		for(int i=n;i>=1;--i){
			for(int j=m;j>=1;--j){
				if(s[i][j]=='#'){
					rr[i][j]=rr[i][j+1]+1;
					dd[i][j]=dd[i+1][j]+1;
				}
			}
		}
		++cas;
		printf("Case #%d:\n",cas);
		while(q--){
			scanf("%d %d %d",&op,&x,&y);
			if(op==1) modify(x,y);
			else printf("%d\n",query(x,y));
		}
	}
}
