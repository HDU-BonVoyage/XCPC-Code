#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct Point{
	int x,y,id;
	bool operator < (const Point &p) const{
		if(x!=p.x) return x<p.x;
		else return y<p.y;
	}
}p[N];
int n,a[N<<1];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d %d",&p[i].x,&p[i].y),p[i].id=i;
	sort(p+1,p+1+n);
	for(int i=1;i<=n;++i) a[i]=p[i].id;
	for(int i=1;i<n;++i) a[n+i]=p[n-i].id;
	printf("%d\n",n*2-1);
	for(int i=1;i<=n*2-1;++i) printf("%d ",a[i]);
}
