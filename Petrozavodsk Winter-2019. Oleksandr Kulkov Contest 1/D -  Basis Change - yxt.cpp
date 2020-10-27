#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll md=1e9+7;
ll qp(ll a,ll b,ll mod){
	ll ret=1;
	a%=mod;
	for(;b;b>>=1){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
	}
	return ret;
}
ll m;
void mul(ll a[],ll b[],ll c[],ll l1,ll l2){
	for(int i=0;i<l1;i++){
		for(int j=0;j<l2;j++){
			c[i+j]+=a[i]*b[j]%md;
			if(c[i+j]>=md) c[i+j]-=md;
		}
	}
	return;
}
ll a[600],b[600];
void polymod(ll c[],ll l1){
	for(int i=l1;i>=m;i--){
		c[i]%=md;
		if(c[i]==0) continue;
		ll t=md-c[i];
		for(int j=1;j<=m;j++){
			c[i-j]=(c[i-j]+t*a[m-j]%md);
			if(c[i-j]>=md) c[i-j]-=md;
		}
		c[i]=0;
	}
	return;
}
ll f[600],g[600],tmp[600];
void gao(ll x){
	for(int i=0;i<2*m;i++){
		f[i]=g[i]=0;
	}
	f[0]=1;
	g[1]=1;
	while(x){
		if(x&1){
			mul(f,g,tmp,m,m);
			for(int i=0;i<2*m;i++){
				f[i]=tmp[i];
				tmp[i]=0;
			}
			polymod(f,m*2);
		}
		mul(g,g,tmp,m,m);
		for(int i=0;i<2*m;i++) g[i]=tmp[i],tmp[i]=0;
		polymod(g,2*m);
		x>>=1;
	}
}
ll mat[200][200];
ll ans[200];
void guass(){
	for(int i=0;i<m;i++){
		int id=0;
		for(int j=i;j<m;j++){
			if(mat[j][i]){
				id=j;break;
			}
		}
		swap(mat[i],mat[id]);
		for(int j=i+1;j<m;j++){
			if(!mat[j][i]) continue;
			ll tmp=qp(mat[i][i],md-2,md)*mat[j][i]%md;
			for(int k=i;k<=m;k++){
				mat[j][k]=(mat[j][k]-mat[i][k]*tmp%md+md)%md;
			}
		}
		
	}
	for(int i=m-1;i>=0;i--){
		ll now=mat[i][m];
		for(int j=i+1;j<m;j++){
			now=(now-ans[j]*mat[i][j]%md+md)%md;
		}
		ans[i]=qp(mat[i][i],md-2,md)*now%md;
	}
}
int main(){
	scanf("%lld",&m);
	for(int i=0;i<m;i++){
		scanf("%lld",&a[m-i-1]);
		a[m-i-1]=(md-a[m-i-1]%md);
	}
	a[m]=1;
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	if(m==1){
		printf("%lld\n",qp(md-a[m-1],b[1],md));
		return 0;
	}
	gao(b[m]);
	for(int i=0;i<m;i++){
		mat[i][m]=f[i];
	}
	for(int i=1;i<=m;i++){
		gao(b[m]-b[i]);
		for(int j=0;j<m;j++) mat[j][i-1]=f[j];
	}
	guass();
	for(int i=0;i<m;i++){
		printf("%lld%c",ans[i]," \n"[i==m-1]);
	}
	return 0;
}
