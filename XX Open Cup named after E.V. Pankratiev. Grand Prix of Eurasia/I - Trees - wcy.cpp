#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
int p[N],a[N],b[N],n,k;
bool cmp(int x,int y){
	int l=0,r=0;
	while(x){
		a[l++]=x%10; x/=10;
	}
	reverse(a,a+l); a[l]=-1;
	while(y){
		b[r++]=y%10; y/=10;
	}
	reverse(b,b+r); b[r]=-1;
	for(int i=0;i<10;++i){
		if(a[i]!=b[i]) return a[i]<b[i];
	}
	return 0;
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i) p[i]=i;
	int m=n-1;
	if(m%k){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	sort(p+1,p+n+1,cmp);
	for(int i=1,r=2;i<=n&&m;++i){
		for(int j=1;j<=k;++j){
			printf("%d %d ",p[i],p[r]); ++r;
		}
		m-=k;
	}
	printf("\n");
}
