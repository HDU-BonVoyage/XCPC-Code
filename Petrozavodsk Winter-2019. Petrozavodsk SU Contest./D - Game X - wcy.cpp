#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
bool getup(ll &L,ll &R){
    ll l,r,mid,rs; rs=n;
    if(n*(n-1)/2<k) return false;
    //printf("ok up\n");
    r=n; l=-1;
    while(l+1<r){
        mid=(l+r)>>1;
        if(-(mid*mid+mid)/2+n*mid>=k) r=mid;
        else l=mid;
    }
    L=r; R=n; return true;
}
bool getdown(ll &L,ll &R){
    ll l,r,mid,rs; rs=n;
    if(k<0) return false;
    //printf("ok down\n");
    r=n+1; l=0;
    while(l+1<r){
        mid=(l+r)>>1;
        if((mid*mid-mid)/2<=k) l=mid;
        else r=mid;
    }
    L=0; R=l; return true;
}
ll l1,l2,r1,r2,ans;
int main(){
    scanf("%lld %lld",&n,&k);
    if(!getup(l1,r1)||!getdown(l2,r2)){
        printf("-1\n");
    }else{
        //printf("%lld %lld\n%lld %lld\n",l1,r1,l2,r2);
        l1=max(l1,l2); r1=min(r1,r2);
        if(l1>r1) printf("-1\n");
        else{
            if(abs(n-l1*2)>abs(n-r1*2)){
                printf("%lld\n",l1*l1-n*l1+(n*n-n)/2);
            }else{
                printf("%lld\n",r1*r1-n*r1+(n*n-n)/2);
            }
        }
    }
}
