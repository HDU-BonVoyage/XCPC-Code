#include <bits/stdc++.h>
using namespace std;
int t,cas; long long a,b,p,q,g;
int main(){
	scanf("%d",&t); cas=0;
	while(t--){
		scanf("%lld %lld",&a,&b); ++cas;
		p=a*(a-1)/2; q=(a+b)*(a+b-1)/2;
		g=__gcd(p,q);
		p/=g; q/=g;
		printf("Case #%d: %lld/%lld\n",cas,p,q);
	}
} 
