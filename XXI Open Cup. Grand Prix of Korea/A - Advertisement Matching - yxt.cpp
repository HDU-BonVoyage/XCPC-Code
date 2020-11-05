#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=501000;
ll a[N],b[N];
ll ptb[N];
struct node{
	ll v;int id;
	bool operator < (const node& b)const{
		return v>b.v;
	}
};
node bb[N],aa[N];
ll seg[N<<2],tag[N<<2];
ll val[N];
void build(int pos,int l,int r){
	if(l>r) return;
	if(l==r){
		seg[pos]=val[l];
		tag[pos]=0;
		return;
	}
	int md=(l+r)>>1;
	build(pos<<1,l,md);build(pos<<1|1,md+1,r);
	seg[pos]=min(seg[pos<<1],seg[pos<<1|1]);
	tag[pos]=0;
	return;
}
void push_down(int pos){
	tag[pos<<1]+=tag[pos];
	tag[pos<<1|1]+=tag[pos];
	seg[pos<<1]+=tag[pos];
	seg[pos<<1|1]+=tag[pos];
	tag[pos]=0;
	return;
}
void modi(int pos,int l,int r,int tl,int tr,int d){
	if(l==tl && r==tr){
		tag[pos]+=d;
		seg[pos]+=d;
		return;
	}
	push_down(pos);
	int md=(l+r)>>1;
	if(tr<=md){
		modi(pos<<1,l,md,tl,tr,d);
	}
	else if(tl>md){
		modi(pos<<1|1,md+1,r,tl,tr,d);
	}
	else{
		modi(pos<<1,l,md,tl,md,d);modi(pos<<1|1,md+1,r,md+1,tr,d);
	}
	seg[pos]=min(seg[pos<<1],seg[pos<<1|1]);
	return;
}
ll dif[N];
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",a+i),aa[i].id=i,aa[i].v=a[i];
	for(int i=1;i<=m;i++) scanf("%lld",b+i),bb[i].id=i,bb[i].v=b[i];
	sort(aa+1,aa+1+n);sort(bb+1,bb+1+m);
	
	for(int i=1;i<=n;i++){
		dif[aa[i].v]--;
	}
	for(int i=N-2;i>=0;i--) dif[i]+=dif[i+1];
	for(int i=1;i<=m;i++) dif[i]+=bb[i].v,ptb[bb[i].id]=i;
	for(int i=N-2;i>=0;i--) dif[i]+=dif[i+1],val[i]+=dif[i];
	build(1,1,N-1);
	int q;
	scanf("%d",&q);
	while(q--){
		int typ,x;
		scanf("%d%d",&typ,&x);
		if(typ==1){
			a[x]++;
			modi(1,1,N-1,1,a[x],-1);
			ll x=seg[1];
			if(x>=0) printf("1\n");
			else printf("0\n");
		}
		else if(typ==2){
			modi(1,1,N-1,1,a[x],1);
			a[x]--;
			ll x=seg[1];
			if(x>=0) printf("1\n");
			else printf("0\n");
		}
		else if(typ==3){
			int pt=lower_bound(bb+1,bb+1+m,(node){b[x],0})-bb;
			b[x]++;
			bb[pt].v++;
			modi(1,1,N-1,1,pt,1);
			ll x=seg[1];
			if(x>=0) printf("1\n");
			else printf("0\n");
		}
		else{
			int pt=upper_bound(bb+1,bb+1+m,(node){b[x],0})-bb-1;
			b[x]--;
			bb[pt].v--;
			modi(1,1,N-1,1,pt,-1);
			ll x=seg[1];
			if(x>=0) printf("1\n");
			else printf("0\n");
		}
	}
	return 0;
}
