#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
const int N = 3e5+10;
ll tr[N<<2],lz[N<<2];
int a[N],b[N],c[N],p[N],n,m,q,op,id,x;
void build(int k,int l,int r){
	lz[k]=0;
	if(l==r){
		tr[k]=c[l]; return;
	}
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	build(lk,l,mid); build(rk,mid+1,r);
	tr[k]=min(tr[lk],tr[rk]);
}
void update(int a,int b,int x,int k,int l,int r){
	if(a>r||b<l) return;
	if(a<=l&&r<=b){
		tr[k]+=x; lz[k]+=x;
		return;
	}
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	if(lz[k]){
		lz[lk]+=lz[k]; lz[rk]+=lz[k];
		tr[lk]+=lz[k]; tr[rk]+=lz[k];
		lz[k]=0;
	}
	update(a,b,x,lk,l,mid); update(a,b,x,rk,mid+1,r);
	tr[k]=min(tr[lk],tr[rk]);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),p[i]=a[i];
	for(int i=1;i<=m;++i) scanf("%d",&b[i]);
	sort(p+1,p+1+n);
	for(int i=1;i<=m;++i) c[1]++,c[b[i]+1]--;
	for(int i=1;i<=n;++i) c[i]+=c[i-1];
	for(int i=1;i<=n;++i) c[i]+=c[i-1]-p[n+1-i];
	build(1,1,n); scanf("%d",&q);
	while(q--){
		scanf("%d %d",&op,&id);
		if(op==1){
			x=upper_bound(p+1,p+1+n,a[id])-p-1;
			p[x]++; x=n+1-x;
			update(x,n,-1,1,1,n); a[id]++;
		}else if(op==2){
			x=lower_bound(p+1,p+1+n,a[id])-p;
			p[x]--; x=n+1-x;
			update(x,n,1,1,1,n); a[id]--;
		}else if(op==3){
			b[id]++;
			if(b[id]<=n) update(b[id],n,1,1,1,n);
		}else{
			if(b[id]<=n) update(b[id],n,-1,1,1,n);
			b[id]--;
		}
		if(tr[1]>=0) printf("1\n");
		else printf("0\n");
	}
}
