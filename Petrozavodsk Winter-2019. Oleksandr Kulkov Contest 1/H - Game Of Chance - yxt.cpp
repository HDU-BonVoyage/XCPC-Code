#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll md=1e9+7;
ll m;
ll qp(ll a,ll b,ll mod){
	ll ret=1;
	a%=mod;
	for(;b;b>>=1){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
	}
	return ret;
}
inline ll pss(ll x){
	return (1+x)*x/2;
}
bool chk(ll d){
	ll lhs=m*d;
	ll rhs=pss(d-1)+pss(m-d);
	return rhs-lhs>=0;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&m);
		ll lb=1,ub=m;
		ll miid,ans;
		while(lb<=ub){
			miid=(lb+ub)>>1;
			if(chk(miid)){
				ans=miid;
				lb=miid+1;
			}
			else ub=miid-1;
		}
		ll cnt=(pss(ans-1)+pss(m-ans))%md-ans*m%md;
		if(cnt<0) cnt+=md;
		//printf("%lld\n",cnt);
		ll coup=ans,coun=m-ans;
		ll r=cnt*qp(m+coun-coup,md-2,md)%md;
		printf("%lld\n",(r+ans)%md);
	}
}
