#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
ll t[100100];
ll s1[100100],s2[100100];
const ll md=1e9+7;
ll inv2=(md+1)/2;
ll qp(ll a,ll b){
    ll ret=1;
    for(;b;b>>=1){
        if(b&1) ret=ret*a%md;
        a=a*a%md;
    }
    return ret;
}
ll fac[100100],ifac[100100];
void pre(){
    fac[0]=1;
    for(int i=1;i<=400;i++){
        fac[i]=fac[i-1]*i%md;
    }
    ifac[400]=qp(fac[400],md-2);
    ifac[0]=1;
    for(int i=399;i>=1;i--){
        ifac[i]=ifac[i+1]*(i+1)%md;
    }
}
ll C(int a,int b){
    return fac[a]*ifac[b]%md*ifac[a-b]%md;
}
ll gao(ll s){
    ll ret=0;
    for(int i=0;i<k-1;i++){
        ret=(ret+C(s,i)*fac[i]%md*(i+1)%md*fac[s-i]%md*fac[n-s-2]%md*C(n,s+2)%md)%md;
    }
    return ret;
}
ll ggao(ll s){
    ll ret=0;
    for(int i=k-1;i<=s;i++){
        ret=(ret+C(s,i)*fac[i]%md*(i+1)%md*fac[s-i]%md*fac[n-s-2]%md*C(n,s+2)%md)%md;
    }
    return ret;
}

void solve1(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            //ll x=t[i],y=t[j];
            if(t[i]<t[j]){
                s1[j]=(s1[j]+fac[n]*inv2%md*t[i]%md)%md;
                int s=0;
                for(int l=1;l<=n;l++){
                    if(t[l]>t[j]) s++;
                }
                s1[j]=(s1[j]+gao(s)*t[i]%md)%md;
                s1[i]=(s1[i]+ggao(s)*t[j]%md)%md;
            }
            else{
                s1[i]=(s1[i]+fac[n]*inv2%md*t[j]%md)%md;
                int s=0;
                for(int l=1;l<=n;l++){
                    if(t[l]>t[i]) s++;
                }
                s1[i]=(s1[i]+gao(s)*t[j]%md)%md;
                s1[j]=(s1[j]+ggao(s)*t[i]%md)%md;
            }
        }
    }
}
void solve2(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            //int x=t[i],y=t[j];
            if(t[i]<t[j]){
                int s=0;
                for(int l=1;l<=n;l++){
                    if(t[l]>t[j]) s++;
                }
                s2[i]=(s2[i]+ggao(s))%md;
            }
            else{
                int s=0;
                for(int l=1;l<=n;l++){
                    if(t[l]>t[i]) s++;
                }
                s2[j]=(s2[j]+ggao(s))%md;
            }
        }
    }
}
int main(){
    pre();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&t[i]);
    }
    solve1();
    solve2();
    for(int i=1;i<=n;i++){
        if(i-1) printf(" ");
        printf("%lld",(s1[i]+t[i]%md*fac[n]%md)%md*s2[i]%md);
    }
    printf("\n");
}
