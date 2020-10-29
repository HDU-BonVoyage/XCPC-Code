#include <bits/stdc++.h>
using namespace std;
const int N = 355;
const int D = 20;

struct Node{
	char s[110];
	int id;
}p[N];
bool cmp(Node a,Node b){
	return strcmp(a.s,b.s)<0;
}
int a[N],b[N],dp[1<<D],pre[N][D],nex[N][D],n,m,k;
bool check(int m){
	m=min(m,20);
	for(int i=1;i<=n;++i) b[i]=p[i].id;
	for(int i=0;i<m;++i) nex[n+1][i]=nex[n][i]=n+1,pre[1][i]=0;
	for(int i=2;i<=n+1;++i){
		for(int j=0;j<m;++j) pre[i][j]=pre[i-1][j];
		if(b[i-1]<m) pre[i][b[i-1]]=i-1;
	}
	for(int i=n-1;i>=0;--i){
		for(int j=0;j<m;++j) nex[i][j]=nex[i+1][j];
		if(b[i+1]<m) nex[i][b[i+1]]=i+1;
	}
	for(int i=1;i<(1<<m);++i){
		for(int j=0;j<m;++j){
			if(i&(1<<j)){
				dp[i]=max(dp[i],nex[dp[i^(1<<j)]][j]);
			}
		}
	}
	if(dp[(1<<m)-1]>n){
		int s=(1<<m)-1,p=n+1,cnt=m;
		while(s){
			for(int i=0;i<m;++i){
				if(s&(1<<i)){
					if(p==0||dp[s^(1<<i)]>=pre[p][i]){
						a[cnt--]=i; s^=(1<<i); p=pre[p][i];
						break;
					}
				}
			}
		}
		return false;
	}else return true;
}
int main(){
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		scanf("%d",&k);
		for(int j=1;j<=k;++j){
			++n; scanf("%s",p[n].s);
			p[n].id=i-1;	
		}
	}
	sort(p+1,p+1+n,cmp);
	if(check(m)) printf("YES\n");
	else{
		printf("NO\n");
		for(int i=1;i<=min(m,20);++i) printf("%d ",a[i]+1);
		if(m>20) for(int i=20;i<m;++i) printf("%d ",i+1);
	}
}
