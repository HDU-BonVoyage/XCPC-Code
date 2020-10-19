#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1<<24;
ll a[N];
int b[N];
ll cas(ll x){
	ll ret=0;
	int k=0;
	while(x){
		ll tmp=x%3;
		x/=3;
		ret+=tmp*(1<<(2*k));
		k++;
	}
	return ret;
}

template <typename T>
void FWT(ll a[],int sz,T gao){
	for(ll d=1;d<sz;d*=4){
		for(ll i=0,t=d*4;i<sz;i+=t){
			for(ll j=0;j<d;j++){
				gao(a[i+j],a[i+j+d],a[i+j+d+d],a[i+j+d+d+d]);
			}
		}
	}
}
template <typename T>
void FWTi(int a[],int sz,T gao){
	for(ll d=1;d<sz;d*=4){
		for(ll i=0,t=d*4;i<sz;i+=t){
			for(ll j=0;j<d;j++){
				gao(a[i+j],a[i+j+d],a[i+j+d+d],a[i+j+d+d+d]);
			}
		}
	}
}
void mex3(ll& a,ll& b,ll& c,ll& d){
	ll x0=a,x1=b,x2=c,x3=d;
	a=x1+x2;
	b=x0+x1+x2;
	c=x0+x2;
	d=x2;
}
void rmex3(ll& a,ll& b,ll& c,ll& d){
	ll x0=a,x1=b,x2=c,x3=d;
	a=x0;
	b=x2-x3;
	c=x1-x0-x2+x3;
}

void mex3i(int& a,int& b,int& c,int& d){
	ll x0=a,x1=b,x2=c,x3=d;
	a=x1+x2;
	b=x0+x1+x2;
	c=x0+x2;
	d=x2;
}
void rmex3i(int& a,int& b,int& c,int& d){
	ll x0=a,x1=b,x2=c,x3=d;
	a=x0;
	b=x2-x3;
	c=x1-x0-x2+x3;
}

int main(){
	int k;
	scanf("%d",&k);
	int sz=1<<(2*k);
	int tsz=1;
	for(int i=1;i<=k;i++){
		tsz*=3;
	}
	for(int i=0;i<tsz;i++){
		scanf("%lld",&a[cas(i)]);
	}
	for(int i=0;i<tsz;i++){
		scanf("%d",&b[cas(i)]);
	}
	FWT(a,sz,mex3);
	FWTi(b,sz,mex3i);
	for(int i=0;i<sz;i++){
		a[i]=a[i]*b[i];
	}
	FWT(a,sz,rmex3);
	for(int i=0;i<tsz;i++){
		if(i) printf(" ");
		printf("%lld",a[cas(i)]);
	}
	printf("\n");
	return 0;
}
