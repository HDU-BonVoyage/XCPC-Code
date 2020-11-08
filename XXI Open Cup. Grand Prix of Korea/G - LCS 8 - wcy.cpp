#include <bits/stdc++.h>
using namespace std;
const int N = 5e4+10;
const int MOD = 1e9+7;
int dp[N][1<<8],n,m,a[10],b[10],to[1<<8][1<<7],px[N][26];
char s[N];
int main(){
	scanf("%s %d",s+1,&m); n=strlen(s+1);
	for(int i=0;i<(1<<(m*2+2));++i){
		int k=0; a[m]=(i>>m)&3; a[m]=3-a[m];
		for(int o=0;o<m;++o) a[o]=(i>>o)&1;
		for(int o=m-1;o>=0;--o) a[o]=a[o+1]-a[o];
		for(int o=m+1;o<=2*m;++o) a[o]=(i>>(o+1))&1;
		for(int o=m+1;o<=2*m;++o) a[o]+=a[o-1];
		for(int j=0;j<(1<<(m*2+1));++j){
			for(int o=0;o<2*m;++o) b[o]=a[o+1]; b[2*m]=0;
			for(int o=0;o<=2*m;++o){
				if(o) b[o]=max(b[o],b[o-1]);
				if((j>>o)&1) b[o]=max(b[o],a[o]+1);
			}
			if(b[m]<4-m){
				to[i][j]=-1; continue;
			}
			int k=0;
			for(int o=0;o<m;++o) k^=(b[o+1]-b[o])<<o;
			for(int o=m+1;o<=2*m;++o) k^=(b[o]-b[o-1])<<(o+1);
			k^=((4-b[m])<<m); to[i][j]=k;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j){
			for(int k=0,o;k<=2*m;++k){
				o=i+k-m;
				if(o>=1&&o<=n&&s[o]=='A'+j) px[i][j]^=(1<<k);
			}
		}
	}
	dp[0][0]=1;
	for(int i=0;i<n;++i){
		for(int j=0,k;j<(1<<(m*2+2));++j){
			if(!dp[i][j]) continue;
			a[m]=(j>>m)&3; a[m]=i-a[m];
			for(int o=0;o<m;++o) a[o]=(j>>o)&1;
			for(int o=m-1;o>=0;--o) a[o]=a[o+1]-a[o];
			for(int o=m+1;o<=2*m;++o) a[o]=(j>>(o+1))&1;
			for(int o=m+1;o<=2*m;++o) a[o]+=a[o-1];
			for(int c=0;c<26;++c){
				k=to[j][px[i+1][c]]; if(k==-1) continue;
				dp[i+1][k]=(dp[i+1][k]+dp[i][j])%MOD;
			}
		}
	}
	int ans=0;
	for(int i=0;i<(1<<(m*2+2));++i) ans=(ans+dp[n][i])%MOD;
	printf("%d\n",ans);
}
