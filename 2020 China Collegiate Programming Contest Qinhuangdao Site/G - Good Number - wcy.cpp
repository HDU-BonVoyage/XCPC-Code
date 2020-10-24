#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
const int INF = 1e9;
ll pw[N],n,k;
ll fpow(ll x,ll p){
	ll rs=1;
	while(p){
		if(p&1ll) rs=rs*x;
		x=x*x; p>>=1;
		if(rs>INF) return INF+1;
		if(x>INF&&p) return INF+1;
	}
	return rs;
}
ll cal(ll x,ll l,ll r){
	return r/x-(l-1)/x;
}
ll solve(ll n,ll k){
	if(k==1) return n;
	else{
		ll rs=0; int tot=1; pw[tot]=1;
		while(1){
			++tot;
			pw[tot]=fpow(tot,k);
			if(pw[tot]>n) break;
		}
		for(int i=1;i<tot;++i){
			rs+=cal(i,pw[i],min(n,pw[i+1]-1));
		}
		return rs;
	}
}
int main(){
	int T,cas=0; scanf("%d",&T);
	while(T--){
		scanf("%lld %lld",&n,&k); ++cas;
		printf("Case #%d: %lld\n",cas,solve(n,k));
	}
}
