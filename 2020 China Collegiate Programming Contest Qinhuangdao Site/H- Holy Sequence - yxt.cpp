#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
ll stir[3300][3300],edw[3300][3300];
inline void mo(ll& x){
	x=(x>=m)?(x-m):x;
}
ll a[3300],b[3300];
int main(){
	int T;
	scanf("%d",&T);int cas=1;
	while(T--){
		scanf("%lld%lld",&n,&m);
		stir[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				stir[i][j]=stir[i-1][j-1]+1ll*stir[i-1][j]*j%m;
				if(stir[i][j]>=m) stir[i][j]-=m;
			}
		}
		for(int i=0;i<=n;i++) edw[0][i]=1;
		for(int i=1;i<=n;i++){
			for(int j=n;j>=0;j--){
				edw[i][j]=1ll*edw[i-1][j]*j%m;
				mo(edw[i][j]);
				if(j<n) edw[i][j]=edw[i-1][j+1]+edw[i][j];
				mo(edw[i][j]);
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				a[j+1]=a[j+1]+stir[i][j]*edw[n-i-1][j+1]%m;
				mo(a[j+1]);
				if(i<n-1){
					a[j+1]=a[j+1]+stir[i][j]*edw[n-i-2][j+1]%m*2*(n-i-1)%m;
					mo(a[j+1]);
				}
				b[j]=b[j]+stir[i][j]*edw[n-i-1][j]%m;
				mo(b[j]);
				if(i<n-1){
					b[j]=b[j]+stir[i][j]*edw[n-i-2][j]%m*2*(n-i-1)%m;
					mo(b[j]);
				}
			}
		}
		b[n+1]=0;
		for(int i=n;i>=1;i--) b[i]=(b[i+1]+b[i])%m;
		printf("Case #%d:\n",cas++);
		for(int i=1;i<=n;i++){
			if(i-1) printf(" ");
			printf("%lld",(a[i]+b[i])%m);
			a[i]=0;b[i]=0;
		}
		printf("\n");
		a[0]=b[0]=0;
	}
	return 0;
}
