#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int mo=1e9+7;
const int maxn=4010;
int n,x,a[maxn];
long long ans,p[maxn],inv[maxn],dp[maxn][2];
long long po(long long a,long long b)
{
    if (b==0) return 1;
    if (b==1) return a%mo;
    long long c=po(a,b/2);
    if (b&1) return c*c%mo*a%mo;else return c*c%mo;
}
long long C(int n,int m){return p[n]*inv[m]%mo*inv[n-m]%mo;}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    p[0]=1; for (int i=1;i<=n;i++) p[i]=p[i-1]*i%mo;
    inv[0]=1; for (int i=1;i<=n;i++) inv[i]=po(p[i],mo-2);
    dp[1][0]=1;
    for (int i=2;i<=n;i++)
     for (int j=1;j<i;j++)
     {
         dp[i][0]=(dp[i][0]+dp[j][1])%mo;
         dp[i][1]=(dp[i][1]+dp[j][0])%mo;
     }
    for (int i=1;i<=n;i++)
    {
        long long now=(dp[i][0]-dp[i][1]+mo)%mo*a[i]%mo;
        ans=(ans+now*C(n-1,i-1)%mo*p[n-i]%mo)%mo;
        //printf("+:%lld -:%lld\n",dp[i][0],dp[i][1]);
    }
    printf("%lld\n",ans*inv[n-1]%mo);
return 0;
}
