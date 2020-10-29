#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=1e6+10;
int n,m,k,sx,sy,num[maxn],cnt;
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&k,&sx,&sy);
	for (int i=1;i<=n;i++)
     for (int j=1;j<=m;j++)
     {
     	int x; scanf("%d",&x);
     	if (x) num[abs(i-sx)+abs(j-sy)+x]++;
	 }
	for (int i=0;i<maxn;i++) if (num[i]) cnt++;
	printf("%d\n",cnt);
	for (int i=1;i<maxn;i++) if (num[i]) printf("%d %d\n",i,num[i]);
return 0;
}
