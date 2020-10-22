#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+10;
int a[N],b[N],p1[N],p2[N],l,r,n,m;
ll ans,tp;
int main(){
	scanf("%d",&n); l=n/2; r=n+1-l;
	m=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]<=l){
			p1[++m]=i;
		}
	}
	m=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
		if(b[i]>=r){
			p2[++m]=i;
		}
	}
	for(int i=1;i<=m;++i) ans+=abs(p2[i]-p1[i]);
	if(n&1){
		m=0;
		for(int i=1;i<=n;++i){
			if(a[i]<=l+1){
				p1[++m]=i;
			}
		}
		m=0;
		for(int i=1;i<=n;++i){
			if(b[i]>=r-1){
				p2[++m]=i;
			}
		}
		for(int i=1;i<=m;++i) tp+=abs(p2[i]-p1[i]);
		ans=min(ans,tp);	
	}
	printf("%lld\n",ans);
}
