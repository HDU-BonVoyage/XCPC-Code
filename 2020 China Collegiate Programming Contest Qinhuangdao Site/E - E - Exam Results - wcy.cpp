#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5+10;
ll a[N],b[N],tt[N]; int n,cnt,m,p;
struct Node{
	int id,op; ll v;
	bool operator < (const Node &rhs) const{
		if(v!=rhs.v) return v>rhs.v;
		else return op<rhs.op;
	}
}o[N];
int tr[N<<2],T;
void build(int k,int l,int r){
	tr[k]=0; if(l==r) return ;
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	build(lk,l,mid); build(rk,mid+1,r);
}
void update(int p,int v){
	int k=1,l=1,r=m,lk,rk,mid; tr[k]+=v;
	while(l<r){
		lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
		if(p<=mid){
			k=lk; r=mid;
		}else{
			k=rk; l=mid+1;
		}
		tr[k]+=v;
	}
}
int query(int a,int b,int k,int l,int r){
	if(a>r||b<l) return 0;
	if(a<=l&&r<=b) return tr[k];
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	return query(a,b,lk,l,mid)+query(a,b,rk,mid+1,r);
}
int ha(ll x){
	return lower_bound(tt+1,tt+1+m,x)-tt;
}
int solve(){
	int rs=0; build(1,1,m);
	for(int i=1;i<=n;++i) update(ha(a[i]),1);
	for(int i=1,j=1;i<=cnt;i=j){
		while(j<=cnt&&o[j].v==o[i].v) ++j;
		int c=ha(o[i].v/100*p);
		if(c<m) rs=max(rs,query(c,m,1,1,m));
		for(int k=i;k<j;++k){
			update(ha(o[k].v),-1);
			if(o[k].op==0) update(ha(b[o[k].id]),1);
		}
		if(tr[1]<n) break;
	}
	return rs;
}
int main(){
	int T; scanf("%d",&T);int cas=0;
	while(T--){ cas++;
		scanf("%d%d",&n,&p); cnt=m=0;
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a[i],&b[i]);
			a[i]*=100; b[i]*=100;
			tt[++m]=a[i]; tt[++m]=b[i];
			++cnt; o[cnt].id=i; o[cnt].op=0; o[cnt].v=a[i];
			++cnt; o[cnt].id=i; o[cnt].op=1; o[cnt].v=b[i];
		}
		sort(o+1,o+1+cnt);
		sort(tt+1,tt+1+m); m=unique(tt+1,tt+1+m)-tt-1;
		printf("Case #%d: %d\n",cas,solve());
	}
}
