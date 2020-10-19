#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1ll*rs*x%MOD;
        x=1ll*x*x%MOD; p>>=1;
    }
    return rs;
}
int main(){
    int t,n,m,ans; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        ans=1ll*fpow(m,n)*fpow(fpow(m,n-1),n-3)%MOD*fpow(m,n-3)%MOD;
        if(n==4&&m%2==0) ans=ans*2%MOD;
        printf("%lld\n",ans);
    }
}
