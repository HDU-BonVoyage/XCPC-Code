#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
u64 xorshift128p(u64 &A, u64 &B) {
	u64 T = A, S = B;
	A = S;
	T ^= T << 23;
	T ^= T >> 17;
	T ^= S ^ (S >> 26);
	B = T;
	return T + S;
}
	
void gen(int n, int L, int X, int Y, u64 A, u64 B, int l[], int r[]) {
	for (int i = 1; i <= n; i ++) {
		l[i] = xorshift128p(A, B) % L + X;
		r[i] = xorshift128p(A, B) % L + Y;
		if (l[i] > r[i]) swap(l[i], r[i]);
	}
}
struct ddq{
	int val[5001000],pos[5001000];
	int ptl,ptr;
	void init(){
		ptl=ptr=1;
	}
	void ins(int p,int v){
		while(ptr>ptl && val[ptr-1]>v){
			ptr--;
		}
		val[ptr]=v;pos[ptr]=p;
		ptr++;
	}
	void del(int p){
		while(pos[ptl]<=p && ptl<ptr) ptl++;
		return;
	}
	int qmin(){
		return val[ptl];
	}
};
ddq ul,ur,dl,dr;
int Ll,Lr,Rl,Rr;
int L[5005000],R[5005000];
ll n,lim,X,Y;
u64 A,B;
ll ans[5005000];
void mLl(){
	dl.del(Ll);
	ul.del(Ll);
	Ll++;
}
void mLr(){
	Lr++;
	ul.ins(Lr,R[Lr]-Lr);
	dl.ins(Lr,-L[Lr]-Lr);
}
void mRl(){
	dr.del(Rl);
	ur.del(Rl);
	Rl++;
}
void mRr(){
	Rr++;
	dr.ins(Rr,-L[Rr]+Rr);
	ur.ins(Rr,R[Rr]+Rr);
}
bool chk(int pos,int d){
	if(pos-(d-1)<1 || pos+(d-1)>n) return 0;
	ll ub=1e18,lb=-1e18;
	ub=min(ub,1ll*ul.qmin()+pos);ub=min(ub,1ll*ur.qmin()-pos);
	lb=max(lb,-1ll*dl.qmin()-pos);lb=max(lb,-1ll*dr.qmin()+pos);
	for(int i=Rr+1;i<=pos+d-1;i++){
		ub=min(ub,1ll*R[i]+i-pos);
		lb=max(lb,1ll*L[i]-(i-pos));
	}
	return ub-lb+1>=2*d-1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T,cas=1;
	cin>>T;
	while(T--){
		cin>>n>>lim>>X>>Y>>A>>B;
		gen(n,lim,X,Y,A,B,L,R);
		ul.init();ur.init();dl.init();dr.init();
		Ll=Rl=1;
		Lr=Rr=0;
		for(int i=1;i<=n;i++){
			ans[i]=ans[i-1]+1;
			mLr();
			if(Rr<i) mRr();
			if(Rl<i) mRl();
			while(!chk(i,ans[i])){
				ans[i]--;
				mLl();
			}
			while(Rr<i+ans[i]-1) mRr();
		}
		cout<<"Case #"<<cas<<": ";
		cas++;
		ll ret=0,pri=1;
		for(int i=1;i<=n;i++){
			ret=(ret+ans[i]*pri%998244353)%998244353;
			pri=pri*3%998244353;
		}
		cout<<ret<<"\n";
	}
	return 0;
}
